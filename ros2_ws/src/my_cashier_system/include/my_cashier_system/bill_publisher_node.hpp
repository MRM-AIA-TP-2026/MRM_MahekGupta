#ifndef BILL_SUBSCRIBER_NODE_HPP_
#define BILL_SUBSCRIBER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"

class BillSubscriberNode : public rclcpp::Node
{
public:
    /**
     * @brief Constructor for the BillSubscriberNode class.
     * Initializes the node and sets up the subscription to the "bill" topic.
     */
    BillSubscriberNode();

private:
    /**
     * @brief Callback function to process incoming bill messages.
     * Updates the inventory and income based on the received bill.
     * 
     * @param msg Shared pointer to the received bill message.
     */
    void process_bill(const tutorial_interfaces::msg::Num::SharedPtr msg);

    rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscriber_; ///< Subscription to the "bill" topic
    int inventory_;    ///< Current inventory count
    double income_;    ///< Total income
};

#endif // BILL_SUBSCRIBER_NODE_HPP_
