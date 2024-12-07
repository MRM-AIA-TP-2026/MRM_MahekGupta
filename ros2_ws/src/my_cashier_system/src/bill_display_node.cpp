#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/bill.hpp>
#include <std_msgs/msg/string.hpp>

class BillMonitorNode : public rclcpp::Node {
public:
    BillMonitorNode() : Node("bill_monitor_node"), last_bill_received_(nullptr) {
        // Create parameter client
        param_client_ = std::make_shared<rclcpp::SyncParametersClient>(this, "bill_processor_node");

        // Subscribe to the bill topic
        bill_subscriber_ = this->create_subscription<tutorial_interfaces::msg::Bill>(
            "bill_topic", 10,
            std::bind(&BillMonitorNode::monitor_bill, this, std::placeholders::_1)
        );

        RCLCPP_INFO(this->get_logger(), "Bill Monitor Node initialized.");
    }

private:
    void monitor_bill(const tutorial_interfaces::msg::Bill::SharedPtr bill_msg) {
        last_bill_received_ = bill_msg;

        RCLCPP_INFO(this->get_logger(),
            "Bill Received - Number: %u, Quantity: %.2f, Price: %.2f, Total: %.2f",
            bill_msg->bill_number, bill_msg->quantity, bill_msg->price, bill_msg->total);

        display_bill();
    }

    void display_bill() {
        if (!param_client_->wait_for_service(std::chrono::seconds(5))) {
            RCLCPP_ERROR(this->get_logger(), "Parameter service not available.");
            return;
        }

        if (last_bill_received_ == nullptr) {
            RCLCPP_WARN(this->get_logger(), "No bill has been received yet.");
            return;
        }

        try {
            // Fetch parameters with default values
            auto inventory = param_client_->get_parameter("inventory", 100.0); // Default value
            auto income = param_client_->get_parameter("total_income", 0.0);   // Default value

            // Log the current state including last bill info
            RCLCPP_INFO(this->get_logger(),
                "=== SYSTEM REPORT ===\n"
                "--- Last Bill Details ---\n"
                "Bill Number: %u\n"
                "Timestamp: %d.%d\n"
                "Quantity: %.2f\n"
                "Price: %.2f\n"
                "Total: %.2f\n"
                "--- System State ---\n"
                "Current Inventory: %.2f\n"
                "Total Income: %.2f",
                last_bill_received_->bill_number,
                last_bill_received_->timestamp.sec,
                last_bill_received_->timestamp.nanosec,
                last_bill_received_->quantity,
                last_bill_received_->price,
                last_bill_received_->total,
                inventory,
                income
            );
        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Failed to fetch parameters: %s", e.what());
        }
    }

    rclcpp::Subscription<tutorial_interfaces::msg::Bill>::SharedPtr bill_subscriber_;
    rclcpp::SyncParametersClient::SharedPtr param_client_;
    tutorial_interfaces::msg::Bill::SharedPtr last_bill_received_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BillMonitorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
