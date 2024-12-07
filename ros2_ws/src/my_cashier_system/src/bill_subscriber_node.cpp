#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/bill.hpp>
#include <thread>
#include <iostream>

class BillProcessorNode : public rclcpp::Node {
public:
    BillProcessorNode() : Node("bill_processor_node") {
        // Declare parameters for inventory and total income
        this->declare_parameter("inventory", 100.0);  // Initial inventory
        this->declare_parameter("total_income", 0.0); // Initial total income

        // Subscribe to the bill topic
        bill_subscriber_ = this->create_subscription<tutorial_interfaces::msg::Bill>(
            "bill_topic", 10,
            std::bind(&BillProcessorNode::process_bill, this, std::placeholders::_1)
        );

        // Start a separate thread for manual updates
        update_thread_ = std::thread(&BillProcessorNode::manual_update, this);
    }

    ~BillProcessorNode() {
        if (update_thread_.joinable()) {
            update_thread_.join();
        }
    }

private:
    void process_bill(const tutorial_interfaces::msg::Bill::SharedPtr bill_msg) {
        // Get the current inventory and total income
        double current_inventory = this->get_parameter("inventory").as_double();
        double current_income = this->get_parameter("total_income").as_double();

        // Update the inventory based on the bill quantity
        double new_inventory = current_inventory - bill_msg->quantity;

        // Update the total income based on the bill total
        double new_income = current_income + bill_msg->total;

        // Set the updated parameters
        this->set_parameter(rclcpp::Parameter("inventory", new_inventory));
        this->set_parameter(rclcpp::Parameter("total_income", new_income));
        //updating the parameters
        
        // Log the updates
        RCLCPP_INFO(this->get_logger(),
            //"Processed Bill #%d:\n"
            //"Quantity: %.2f, Total: %.2f\n"
            "Updated Inventory: %.2f -> %.2f\n"
            "Updated Total Income: %.2f -> %.2f",
            //bill_msg->bill_number, bill_msg->quantity, bill_msg->total,
            current_inventory, new_inventory,
            current_income, new_income
        );
    }

    void manual_update() {
        while (rclcpp::ok()) {
            std::string choice;
            std::cout << "\nWhat do you want to update? (inventory/income/exit): ";
            std::cin >> choice;

            if (choice == "inventory") {
                double new_inventory;
                std::cout << "Enter new inventory value: ";
                std::cin >> new_inventory;
                this->set_parameter(rclcpp::Parameter("inventory", new_inventory));
                RCLCPP_INFO(this->get_logger(), "Inventory manually updated to: %.2f", new_inventory);

            } else if (choice == "income") {
                double new_income;
                std::cout << "Enter new total income value: ";
                std::cin >> new_income;
                this->set_parameter(rclcpp::Parameter("total_income", new_income));
                RCLCPP_INFO(this->get_logger(), "Total Income manually updated to: %.2f", new_income);

            } else if (choice == "exit") {
                RCLCPP_INFO(this->get_logger(), "Exiting manual update mode...");
                break;

            } else {
                std::cout << "Invalid choice. Please choose 'inventory', 'income', or 'exit'.\n";
            }
        }
    }

    rclcpp::Subscription<tutorial_interfaces::msg::Bill>::SharedPtr bill_subscriber_;
    std::thread update_thread_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BillProcessorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
