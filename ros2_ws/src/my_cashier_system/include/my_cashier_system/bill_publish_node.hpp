#ifndef MY_CASHIER_SYSTEM__BILL_PUBLISHER_NODE_HPP_
#define MY_CASHIER_SYSTEM__BILL_PUBLISHER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"  // Include the Num message

class BillPublisherNode : public rclcpp::Node
{
public:
    BillPublisherNode();

private:
    void publish_bill();
    rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

#endif  // MY_CASHIER_SYSTEM__BILL_PUBLISHER_NODE_HPP_

