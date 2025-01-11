#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/bill.hpp>
#include <std_srvs/srv/trigger.hpp>  
#include <thread>
#include <iostream>

class ManagerNode : public rclcpp::Node {
public:
    ManagerNode() : Node("manager_node") {
        // Declare parameters for inventory and total income
        this->declare_parameter<int>("inventory", 100);  // Initial inventory
        this->declare_parameter<double>("income", 0.0);  // Initial total income

        // Create subscription to the bill topic
        subscriber_ = this->create_subscription<tutorial_interfaces::msg::Bill>(
            "bill_topic", 10, std::bind(&ManagerNode::bill_callback, this, std::placeholders::_1));

        // Create a service client for triggering updates
        client_ = this->create_client<std_srvs::srv::Trigger>("update_parameters");

        // Start a separate thread for manual updates
        update_thread_ = std::thread(&ManagerNode::manual_update, this);

        RCLCPP_INFO(this->get_logger(), "Manager Node Started");
    }

    ~ManagerNode() {
        if (update_thread_.joinable()) {
            update_thread_.join();
        }
    }

private:
    void bill_callback(const tutorial_interfaces::msg::Bill::SharedPtr msg) {
        // Get the current inventory and total income from parameters
        int inventory = this->get_parameter("inventory").as_int();
        double income = this->get_parameter("income").as_double();

        // Update the inventory and income based on the bill
        inventory -= msg->quantity;
        income += msg->total;

        // Set the updated parameters
        this->set_parameter(rclcpp::Parameter("inventory", inventory));
        this->set_parameter(rclcpp::Parameter("income", income));

        // Log the updates
         RCLCPP_INFO(this->get_logger(),
            "Processed Bill: Quantity: %.2f, Total: %.2f\nUpdated Inventory: %.2f -> %.2f\nUpdated Income: %.2f -> %.2f",
            msg->quantity, msg->total, static_cast<float>(inventory + msg->quantity), static_cast<float>(inventory), static_cast<float>(income - msg->total), static_cast<float>(income));


        // Optionally, trigger the service to process the update
        auto request = std::make_shared<std_srvs::srv::Trigger::Request>();
        client_->async_send_request(request);
    }

    void manual_update() {
        while (rclcpp::ok()) {
            std::string choice;
            std::cout << "\nWhat do you want to update? (inventory/income/exit): ";
            std::cin >> choice;

            if (choice == "inventory") {
                int new_inventory;
                std::cout << "Enter new inventory value: ";
                std::cin >> new_inventory;
                this->set_parameter(rclcpp::Parameter("inventory", new_inventory));
                RCLCPP_INFO(this->get_logger(), "Inventory manually updated to: %d", new_inventory);

            } else if (choice == "income") {
                double new_income;
                std::cout << "Enter new total income value: ";
                std::cin >> new_income;
                this->set_parameter(rclcpp::Parameter("income", new_income));
                RCLCPP_INFO(this->get_logger(), "Total Income manually updated to: %.2f", new_income);

            } else if (choice == "exit") {
                RCLCPP_INFO(this->get_logger(), "Exiting manual update mode...");
                break;

            } else {
                std::cout << "Invalid choice. Please choose 'inventory', 'income', or 'exit'.\n";
            }
        }
    }

    rclcpp::Subscription<tutorial_interfaces::msg::Bill>::SharedPtr subscriber_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client_;
    std::thread update_thread_;  // Thread for manual updates
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ManagerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
