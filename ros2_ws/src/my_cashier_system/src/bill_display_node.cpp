#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/bill.hpp"  // Corrected the include to match your file structure
#include <iostream>
#include <rclcpp/parameter_client.hpp>  // For SyncParametersClient

class MonitorNode : public rclcpp::Node {
public:
    MonitorNode() : Node("monitor_node") {
        // Subscribe to the bill topic
        subscriber_ = this->create_subscription<tutorial_interfaces::msg::Bill>(
            "bill_topic", 10, std::bind(&MonitorNode::bill_callback, this, std::placeholders::_1));

        // Create SyncParametersClient for accessing parameters of the 'manager_node'
        parameter_client_ = std::make_shared<rclcpp::SyncParametersClient>(this, "manager_node");

        RCLCPP_INFO(this->get_logger(), "Monitor Node Started. Press Enter to display the last bill and parameters.");
    }

    void spin_with_input() {
        while (rclcpp::ok()) {
            if (std::cin.peek() != EOF) {
                std::cin.get();  // Wait for user input (Enter key)
                print_status();
            }

            rclcpp::spin_some(this->get_node_base_interface());
        }
    }

private:
    void bill_callback(const tutorial_interfaces::msg::Bill::SharedPtr msg) {
        last_bill_ = *msg;  // Save the last received bill
    }

    void print_status() {
        // Wait for the 'manager_node' service to be available
        if (!parameter_client_->wait_for_service(std::chrono::seconds(2))) {
            RCLCPP_WARN(this->get_logger(), "Manager Node not available for parameter fetch.");
            return;
        }

        try {
            // Fetch 'inventory' and 'income' parameters from 'manager_node'
            auto inventory = parameter_client_->get_parameter<int>("inventory");
            auto income = parameter_client_->get_parameter<double>("income");

            // Log the last received bill details
            if (last_bill_.bill_number > 0) {
                RCLCPP_INFO(this->get_logger(),
            "Last Bill - Number: %d, Quantity: %f, Total: %.2f",
            last_bill_.bill_number, last_bill_.quantity, last_bill_.total);

                
            } else {
                RCLCPP_WARN(this->get_logger(), "No bill received yet!");
            }

            // Log the current parameters (inventory and income)
            RCLCPP_INFO(this->get_logger(), "Current Inventory: %d, Income: %.2f", inventory, income);
        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Failed to fetch parameters: %s", e.what());
        }
    }

    rclcpp::Subscription<tutorial_interfaces::msg::Bill>::SharedPtr subscriber_;
    rclcpp::SyncParametersClient::SharedPtr parameter_client_;
    tutorial_interfaces::msg::Bill last_bill_;  // To store the last received bill
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto monitor_node = std::make_shared<MonitorNode>();
    monitor_node->spin_with_input();  // Start the node and wait for user input

    rclcpp::shutdown();
    return 0;
}
