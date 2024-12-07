#ifndef BILL_DISPLAY_NODE_HPP
#define BILL_DISPLAY_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"

class BillDisplayNode : public rclcpp::Node
{
public:
    BillDisplayNode(); // Constructor

    void display_info(); // Function to display the last bill, inventory, and income

private:
    void update_last_bill(const tutorial_interfaces::msg::Num::SharedPtr msg); // Callback for subscription

    rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscriber_;
    tutorial_interfaces::msg::Num last_bill_; // Stores the last bill received
    int inventory_;    // Tracks current inventory
    double income_;    // Tracks total income
};

#endif // BILL_DISPLAY_NODE_HPP
