#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <cmath>


class GpsNavigator : public rclcpp::Node
{
public:
    GpsNavigator()
        : Node("gps_navigator")
    {
        target_lat_=0.00052;
        target_lon_=0.00030;
        target_reached_=false;

        gps_subscriber_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
            "/gps", 10, std::bind(&GpsNavigator::gpsCallback, this, std::placeholders::_1));

        imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu", 10, std::bind(&GpsNavigator::imuCallback, this, std::placeholders::_1));

        cmd_vel_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        RCLCPP_INFO(this->get_logger(), "GPS Navigator Node Initialized");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;

    double target_lat_;
    double target_lon_;
    double last_lat_;
    double last_lon_;
    double current_heading_=0.0;
    bool target_reached_;

    void gpsCallback(const sensor_msgs::msg::NavSatFix::SharedPtr msg)
    {
        if (target_reached_) {
            publishVelocity(0.0, 0.0);
            return;
        }

        double current_lat = msg->latitude;
        double current_lon = msg->longitude;

        if (last_lat_ && last_lon_) {
            current_heading_ = calculateHeading(last_lat_, last_lon_, current_lat, current_lon);
        }

        last_lat_ = current_lat;
        last_lon_ = current_lon;

        double distance = haversineDistance(current_lat, current_lon, target_lat_, target_lon_);
        double desired_heading = calculateHeading(current_lat, current_lon, target_lat_, target_lon_);
        double angular_error = normalizeAngle(desired_heading - current_heading_);

        RCLCPP_INFO(this->get_logger(), "Distance to Target: %.2f m", distance);
        RCLCPP_INFO(this->get_logger(), "Current Heading: %.2f rad, Desired Heading: %.2f rad, Angular Error: %.2f rad",
                    current_heading_, desired_heading, angular_error);

        if (distance < 1.0) {
            publishVelocity(0.0, 0.0);
            RCLCPP_INFO(this->get_logger(), "Target Reached.");
            target_reached_ = true;
            return;
        }

        double angular_velocity = angular_error * 3.0;
        double linear_velocity = std::max(0.0, 1.0 - std::abs(angular_error));

        publishVelocity(linear_velocity, angular_velocity);
    }

    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        auto q = msg->orientation;
        double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        current_heading_ = std::atan2(siny_cosp, cosy_cosp);

        RCLCPP_INFO(this->get_logger(), "Updated IMU Heading: %.2f radians", current_heading_);
    }

    double haversineDistance(double lat1, double lon1, double lat2, double lon2)
    {
        const double R = 6371000;
        double dlat = degreesToRadians(lat2 - lat1);
        double dlon = degreesToRadians(lon2 - lon1);
        double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
                   std::cos(degreesToRadians(lat1)) * std::cos(degreesToRadians(lat2)) *
                   std::sin(dlon / 2) * std::sin(dlon / 2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
        return R * c;
    }

    double calculateHeading(double lat1, double lon1, double lat2, double lon2)
    {
        double dlon = degreesToRadians(lon2 - lon1);
        double y = std::sin(dlon) * std::cos(degreesToRadians(lat2));
        double x = std::cos(degreesToRadians(lat1)) * std::sin(degreesToRadians(lat2)) -
                   std::sin(degreesToRadians(lat1)) * std::cos(degreesToRadians(lat2)) * std::cos(dlon);
        return std::atan2(y, x);
    }

    double normalizeAngle(double angle)
    {
        while (angle > M_PI)
            angle -= 2 * M_PI;
        while (angle < -M_PI)
            angle += 2 * M_PI;
        return angle;
    }

    double degreesToRadians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    void publishVelocity(double linear, double angular)
    {
        geometry_msgs::msg::Twist twist_msg;
        twist_msg.linear.x = linear;
        twist_msg.angular.z = angular;
        cmd_vel_publisher_->publish(twist_msg);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GpsNavigator>());
    rclcpp::shutdown();
    return 0;
}
