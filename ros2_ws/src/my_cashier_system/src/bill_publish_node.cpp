#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/bill.hpp>
#include <iostream>

class BillPublisherNode : public rclcpp::Node {
public:
    BillPublisherNode() : Node("bill_publisher_node") {
        // Create a publisher for Bill messages
        bill_publisher_ = this->create_publisher<tutorial_interfaces::msg::Bill>("bill_topic", 10);

        // Initialize bill number
        bill_number_ = 0;
    }

    void run() {
        // Loop to allow user input for multiple bills
        while (rclcpp::ok()) {
            tutorial_interfaces::msg::Bill bill_msg;

            // Increment bill number
            bill_number_++;

            // Set timestamp for the bill
            bill_msg.timestamp = this->now();

            // Prompt user for bill details
            std::cout << "Enter details for Bill #" << bill_number_ << std::endl;

            std::cout << "Enter quantity: ";
            std::cin >> bill_msg.quantity;

            // Check for invalid input
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid number for quantity." << std::endl;
                continue;
            }

            std::cout << "Enter price: ";
            std::cin >> bill_msg.price;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid number for price." << std::endl;
                continue;
            }

            // Calculate total
            bill_msg.total = bill_msg.quantity * bill_msg.price;

            // Set the bill number
            bill_msg.bill_number = bill_number_;

            // Publish the bill message
            bill_publisher_->publish(bill_msg);

            // Log the bill details
            RCLCPP_INFO(this->get_logger(),
                "Published Bill #%d: Qty: %.2f, Price: %.2f, Total: %.2f",
                bill_msg.bill_number, bill_msg.quantity,
                bill_msg.price, bill_msg.total);

            // Ask user if they want to continue
            std::cout << "Press 'q' to quit or any other key to continue: ";
            char input;
            std::cin >> input;
            if (input == 'q' || input == 'Q') {
                break;
            }
        }
    }

private:
    rclcpp::Publisher<tutorial_interfaces::msg::Bill>::SharedPtr bill_publisher_;
    uint32_t bill_number_;
};

int main(int argc, char** argv) {
    // Initialize ROS2
    rclcpp::init(argc, argv);

    // Create a shared pointer to the BillPublisherNode
    auto node = std::make_shared<BillPublisherNode>();

    // Run the node and prompt user for bill details
    node->run();

    // Shut down ROS2
    rclcpp::shutdown();
    return 0;
}
