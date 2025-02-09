#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <cmath>
#include <iostream>

// PID Controller for smooth heading correction
class PIDController {
public:
    PIDController(double Kp, double Ki, double Kd) 
        : Kp_(Kp), Ki_(Ki), Kd_(Kd), prev_error_(0), integral_(0) {}

    double compute(double error) {
        integral_ += error;
        double derivative = error - prev_error_;
        prev_error_ = error;

        // Compute PID output
        return Kp_ * error + Ki_ * integral_ + Kd_ * derivative;
    }

private:
    double Kp_, Ki_, Kd_;
    double prev_error_, integral_;
};

class GpsNavigator : public rclcpp::Node {
public:
    GpsNavigator() : Node("gps_navigator"), pid_heading_(1.0, 0.0, 0.1){
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

        // PID controller initialization for heading control
        pid_heading_ = PIDController(1.0, 0.0, 0.1);  // Example PID parameters
    }

private:
    const double EARTH_RADIUS = 6371000.0;  // meters
    const double ARRIVAL_THRESHOLD = 0.3;   // meters

    double target_lat_, target_lon_;
    double current_heading_ = 0.0;
    bool reached_target_ = false;

    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    PIDController pid_heading_;

    void gpsCallback(const sensor_msgs::msg::NavSatFix::SharedPtr msg) {
        if (reached_target_) {
            publishVelocity(0.0, 0.0);
            return;
        }

        double distance = getDistance(msg->latitude, msg->longitude);
        double desired_heading = getBearing(msg->latitude, msg->longitude);
        double heading_error = desired_heading - current_heading_;

        // Normalize heading error to [-pi, pi]
        while (heading_error > M_PI) heading_error -= 2 * M_PI;
        while (heading_error < -M_PI) heading_error += 2 * M_PI;

        if (distance < ARRIVAL_THRESHOLD) {
            RCLCPP_INFO(get_logger(), "Target reached!");
            reached_target_ = true;
            publishVelocity(0.0, 0.0);
            return;
        }

        // Use PID controller to compute smoother angular velocity
        double angular_vel = pid_heading_.compute(heading_error);

        // Dynamically adjust linear velocity based on distance
        double linear_vel = std::min(distance / 5.0, 1.0);  // Example: Move faster if further

        RCLCPP_INFO(get_logger(), "Distance: %.2f m, Heading Error: %.2f rad", 
                    distance, heading_error);
        
        publishVelocity(linear_vel, angular_vel);
    }

    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        auto q = msg->orientation;
        
        // Roll (x-axis rotation)
        double sinr_cosp = 2.0 * (q.w * q.x + q.y * q.z);
        double cosr_cosp = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
        double roll = std::atan2(sinr_cosp, cosr_cosp);

        // Pitch (y-axis rotation)
        double sinp = 2.0 * (q.w * q.y - q.z * q.x);
        double pitch;
        if (std::abs(sinp) >= 1)
            pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            pitch = std::asin(sinp);

        // Yaw (z-axis rotation)
        double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        current_heading_ = std::atan2(siny_cosp, cosy_cosp);
    }

    double getDistance(double lat1, double lon1) {
        // Convert to radians
        lat1 *= M_PI / 180.0;
        lon1 *= M_PI / 180.0;
        double lat2 = target_lat_ * M_PI / 180.0;
        double lon2 = target_lon_ * M_PI / 180.0;

        // Haversine formula
        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
                   std::cos(lat1) * std::cos(lat2) *
                   std::sin(dlon / 2) * std::sin(dlon / 2);
        return EARTH_RADIUS * 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
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

        // Normalize inline before returning
        double bearing = M_PI + M_PI_2 - std::atan2(y, x);
        while (bearing > M_PI) bearing -= 2 * M_PI;
        while (bearing < -M_PI) bearing += 2 * M_PI;

        return bearing;
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
