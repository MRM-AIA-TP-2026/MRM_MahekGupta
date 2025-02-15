#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <algorithm>

// PID Controller for smooth heading correction
class PIDController {
public:
    PIDController(double Kp, double Ki, double Kd) 
        : Kp_(Kp), Ki_(Ki), Kd_(Kd), prev_error_(0), integral_(0) {}

    double compute(double error) {
        integral_ += error;
        double derivative = error - prev_error_;
        prev_error_ = error;
        return Kp_ * error + Ki_ * integral_ + Kd_ * derivative;
    }

private:
    double Kp_, Ki_, Kd_;
    double prev_error_, integral_;
};

class GpsNavigator : public rclcpp::Node {
public:
    GpsNavigator() : Node("gps_navigator"), pid_heading_(1.0, 0.0, 0.1) {
        // Declare parameters
        declare_parameter("min_linear_velocity", 0.1);
        declare_parameter("max_linear_velocity", 1.0);
        declare_parameter("base_angular_velocity", 0.5);
        declare_parameter("obstacle_threshold", 1.0);
        declare_parameter("arrival_threshold", 0.3);
        
        // Get parameters
        min_linear_velocity_ = get_parameter("min_linear_velocity").as_double();
        max_linear_velocity_ = get_parameter("max_linear_velocity").as_double();
        base_angular_velocity_ = get_parameter("base_angular_velocity").as_double();
        obstacle_threshold_ = get_parameter("obstacle_threshold").as_double();
        arrival_threshold_ = get_parameter("arrival_threshold").as_double();
        
        std::cout << "Enter target latitude: ";
        std::cin >> target_lat_;
        std::cout << "Enter target longitude: ";
        std::cin >> target_lon_;
        
        RCLCPP_INFO(get_logger(), "Target set to: %.6f, %.6f", target_lat_, target_lon_);
        
        gps_sub_ = create_subscription<sensor_msgs::msg::NavSatFix>(
            "/gps", 10, std::bind(&GpsNavigator::gpsCallback, this, std::placeholders::_1));
            
        imu_sub_ = create_subscription<sensor_msgs::msg::Imu>(
            "/imu", 10, std::bind(&GpsNavigator::imuCallback, this, std::placeholders::_1));
            
        vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        lidar_sub_ = create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&GpsNavigator::lidarCallback, this, std::placeholders::_1));

        // PID controller initialization for heading control
        pid_heading_ = PIDController(1.0, 0.0, 0.1);  // Example PID parameters
    }

private:
    // Constants
    const double EARTH_RADIUS = 6371000.0;  // meters
    
    // Parameters (now dynamically configurable)
    double min_linear_velocity_;
    double max_linear_velocity_;
    double base_angular_velocity_;
    double obstacle_threshold_;
    double arrival_threshold_=0.5;

    // State variables
    double target_lat_, target_lon_;
    double current_heading_ = 0.0;
    bool reached_target_ = false;
    bool obstacle_detected_ = false;
    double front_dist_ = std::numeric_limits<double>::infinity();
    double right_dist_ = std::numeric_limits<double>::infinity();
    bool gps = true;
    bool goal_closer = false;
    double start_lat = 0;
    double start_lon = 0;
    double goal_heading = 0;
    double rover_heading = 0;
    double m_error = 0;
    double hit_target_lat = 0;
    double hit_target_lon = 0;
    bool hit_point_marked = false;
    bool leave_point_marked = false;
    double distance = 0;
    double current_lat = 0;
    double current_lon = 0;
    double last_heading_error = 0;

    // ROS2 components
    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_sub_;
    PIDController pid_heading_;

    void gpsCallback(const sensor_msgs::msg::NavSatFix::SharedPtr msg) {
        if (reached_target_) {
            publishVelocity(0.0, 0.0);
            return;
        }

        current_lat = msg->latitude;
        current_lon = msg->longitude;

        if (start_lat == 0 && start_lon == 0) {
            start_lat = current_lat;
            start_lon = current_lon;
            goal_heading = calculateBearing(start_lat, start_lon, target_lat_, target_lon_);
        }

        rover_heading = calculateBearing(start_lat, start_lon, current_lat, current_lon);
        m_error = std::abs(goal_heading - rover_heading);

        if (hit_point_marked) {
            RCLCPP_INFO(this->get_logger(), "Hit point marked at: %.6f, %.6f", hit_target_lat, hit_target_lon);
        }

        distance = getDistance(current_lat, current_lon);
        if (distance < arrival_threshold_) {
            RCLCPP_INFO(get_logger(), "Target reached!");
            reached_target_ = true;
            publishVelocity(0.0, 0.0);
            return;
        }

        double desired_heading = getBearing(current_lat, current_lon);
        double heading_error = desired_heading - current_heading_;
        normalizeAngle(heading_error);
        last_heading_error = heading_error;

        if (gps|| goal_closer) {
            // Dynamic velocity control based on distance and heading error
            double linear_vel = calculateDynamicLinearVelocity(distance, heading_error);
            double angular_vel = calculateDynamicAngularVelocity(heading_error);
            
            publishVelocity(linear_vel, angular_vel);
            RCLCPP_INFO(get_logger(), "Distance: %.2f m, Heading Error: %.2f rad, Linear Vel: %.2f, Angular Vel: %.2f", 
                        distance, heading_error, linear_vel, angular_vel);
        }
    }

    double calculateDynamicLinearVelocity(double distance, double heading_error) {
       
        double dist_factor = std::min(distance / 8.0, 1.0);
        
        
        double heading_factor = std::cos(heading_error * 0.5);  
        heading_factor = std::max(heading_factor, 0.2);  
        
        
        double obstacle_factor = 1.0;
        if (obstacle_detected_) {
            double min_dist = std::min(front_dist_, right_dist_);
            if (min_dist < obstacle_threshold_ * 2.0) {
                obstacle_factor = min_dist / (obstacle_threshold_ * 2.0);
                obstacle_factor = std::max(obstacle_factor, 0.3);  
            }
        }
        
       
        double velocity = max_linear_velocity_ * dist_factor * heading_factor * obstacle_factor;
        
        
        return std::max(velocity, min_linear_velocity_);
    }

    double calculateDynamicAngularVelocity(double heading_error) {
       
        double base_angular = pid_heading_.compute(heading_error);
        
        
        double error_factor = std::min(std::abs(heading_error) / M_PI, 1.0);
        double scaled_angular = base_angular * (0.5 + 0.5 * error_factor);
        
       
        double max_angular = base_angular_velocity_ * (1.0 + error_factor);
        
        if (scaled_angular > max_angular) {
            scaled_angular = max_angular;
        } else if (scaled_angular < -max_angular) {
            scaled_angular = -max_angular;
        }
        
        return scaled_angular;
    }

    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        auto q = msg->orientation;
        // Yaw (z-axis rotation)
        double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        current_heading_ = std::atan2(siny_cosp, cosy_cosp);
    }

    bool obstacleDetected(const sensor_msgs::msg::LaserScan::SharedPtr& msg) {
        for (const auto& range : msg->ranges) {
            if (!std::isinf(range) && !std::isnan(range) && range < obstacle_threshold_) {
                return true;
            }
        }
        return false;
    }

    void lidarCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
        std::map<std::string, double> regions = getLidarRegions(msg);
        front_dist_ = regions["front"];
        right_dist_ = regions["right"];

        double min_obstacle_distance = std::min({regions["right"], regions["front"]});
        if (distance < min_obstacle_distance) {
            goal_closer = true;
            gps = true;
            obstacle_detected_ = false;
            hit_point_marked = false;
        } else {
            goal_closer = false;
            if (obstacleDetected(msg)) {
                gps = false;
                obstacle_detected_ = true;
                boundaryFollower();
            } else {
                obstacle_detected_ = false;
            }
        }
    }

    void boundaryFollower() {
        if (front_dist_ < obstacle_threshold_) {
            if (!hit_point_marked) {
                hit_point_marked = true;
                leave_point_marked = false;
                hit_target_lat = current_lat;
                hit_target_lon = current_lon;
                gps = false;
            }
            
           
            double rotation_speed = base_angular_velocity_ * 
                                    (1.0 + std::max(0.0, (obstacle_threshold_ - front_dist_)) / obstacle_threshold_);
            
            publishVelocity(0.0, rotation_speed);
        } else {
            if (!leave_point_marked) {
                
                double linear_vel = calculateWallFollowingSpeed();
                double angular_vel = calculateWallFollowingTurn();
                publishVelocity(linear_vel, angular_vel);
            }
        }

        if ((m_error < 0.1 && haversineDistance(hit_target_lat, hit_target_lon, current_lat, current_lon) > 2.0)) {
            if (!gps) {
                RCLCPP_INFO(get_logger(), "Switching back to GPS control");
            }
            gps = true;
            leave_point_marked = true;
            hit_point_marked = false;
        }
    }
    
    double calculateWallFollowingSpeed() {
        
        double speed_factor = front_dist_ / (obstacle_threshold_ * 3.0);
        speed_factor = std::min(std::max(speed_factor, 0.3), 1.0);  
        
        return min_linear_velocity_ + 
               (max_linear_velocity_ - min_linear_velocity_) * 0.5 * speed_factor;
    }
    
    double calculateWallFollowingTurn() {
        
        const double ideal_wall_distance = obstacle_threshold_ * 1.0;
        
       
        double turn_rate = 0.0;
        
        if (right_dist_ < obstacle_threshold_ * 0.7) {
            
            turn_rate = base_angular_velocity_ * 
                        (1.0 - right_dist_ / (obstacle_threshold_ * 0.7));
        } else if (right_dist_ > ideal_wall_distance) {
           
            turn_rate = -base_angular_velocity_ * 0.5 * 
                        std::min((right_dist_ - ideal_wall_distance) / ideal_wall_distance, 1.0);
        }
        
        return turn_rate;
    }

    std::map<std::string, double> getLidarRegions(const sensor_msgs::msg::LaserScan::SharedPtr& msg) {
        std::map<std::string, double> regions;
        
        // Handle empty ranges array
        if (msg->ranges.empty()) {
            regions["right"] = std::numeric_limits<double>::infinity();
            regions["front"] = std::numeric_limits<double>::infinity();
            return regions;
        }
        
        const int size = msg->ranges.size();
        const int right_start = static_cast<int>(270.0 / 360.0 * size);
        const int right_end = static_cast<int>(330.0 / 360.0 * size);
        const int front_start = static_cast<int>(330.0 / 360.0 * size);
        const int front_end_1 = size;
        const int front_start_2 = 0;
        const int front_end_2 = static_cast<int>(30.0 / 360.0 * size);

        // Filter out inf and nan values for right region
        std::vector<double> filtered_right;
        for (int i = right_start; i < right_end && i < size; i++) {
            if (!std::isinf(msg->ranges[i]) && !std::isnan(msg->ranges[i])) {
                filtered_right.push_back(msg->ranges[i]);
            }
        }
        
        regions["right"] = filtered_right.empty() ? 
                          std::numeric_limits<double>::infinity() : 
                          *std::min_element(filtered_right.begin(), filtered_right.end());

        // Filter out inf and nan values for front regions
        std::vector<double> filtered_front_1, filtered_front_2;
        for (int i = front_start; i < front_end_1; i++) {
            if (!std::isinf(msg->ranges[i]) && !std::isnan(msg->ranges[i])) {
                filtered_front_1.push_back(msg->ranges[i]);
            }
        }
        for (int i = front_start_2; i < front_end_2 && i < size; i++) {
            if (!std::isinf(msg->ranges[i]) && !std::isnan(msg->ranges[i])) {
                filtered_front_2.push_back(msg->ranges[i]);
            }
        }
        
        double front_min_1 = filtered_front_1.empty() ? 
                            std::numeric_limits<double>::infinity() : 
                            *std::min_element(filtered_front_1.begin(), filtered_front_1.end());
        double front_min_2 = filtered_front_2.empty() ? 
                            std::numeric_limits<double>::infinity() : 
                            *std::min_element(filtered_front_2.begin(), filtered_front_2.end());
        
        regions["front"] = std::min(front_min_1, front_min_2);

        return regions;
    }

    double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
        // Convert to radians
        lat1 *= M_PI / 180.0;
        lon1 *= M_PI / 180.0;
        lat2 *= M_PI / 180.0;
        lon2 *= M_PI / 180.0;

        // Haversine formula
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
                   std::cos(lat1) * std::cos(lat2) *
                   std::sin(dlon / 2) * std::sin(dlon / 2);
        return EARTH_RADIUS * 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    }

    double getDistance(double lat1, double lon1) {
        return haversineDistance(lat1, lon1, target_lat_, target_lon_);
    }

    double getBearing(double lat1, double lon1) {
        // Convert to radians
        lat1 *= M_PI / 180.0;
        lon1 *= M_PI / 180.0;
        double lat2 = target_lat_ * M_PI / 180.0;
        double lon2 = target_lon_ * M_PI / 180.0;

        double dlon = lon2 - lon1;
        double y = std::sin(dlon) * std::cos(lat2);
        double x = std::cos(lat1) * std::sin(lat2) -
                   std::sin(lat1) * std::cos(lat2) * std::cos(dlon);

        double bearing = M_PI + M_PI_2 - std::atan2(y, x);
        normalizeAngle(bearing);
        return bearing;
    }

    double calculateBearing(double lat1, double lon1, double lat2, double lon2) {
        // Convert to radians
        lat1 *= M_PI / 180.0;
        lon1 *= M_PI / 180.0;
        lat2 *= M_PI / 180.0;
        lon2 *= M_PI / 180.0;

        double dlon = lon2 - lon1;
        double y = std::sin(dlon) * std::cos(lat2);
        double x = std::cos(lat1) * std::sin(lat2) -
                   std::sin(lat1) * std::cos(lat2) * std::cos(dlon);

        double bearing = M_PI + M_PI_2 - std::atan2(y, x);
        normalizeAngle(bearing);
        return bearing;
    }

    void normalizeAngle(double& angle) {
        while (angle > M_PI) angle -= 2 * M_PI;
        while (angle < -M_PI) angle += 2 * M_PI;
    }

    void publishVelocity(double linear, double angular) {
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = linear;
        msg.angular.z = angular;
        vel_pub_->publish(msg);
    }
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GpsNavigator>());
    rclcpp::shutdown();
    return 0;
}