// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tutorial_interfaces:msg/Bill.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__MSG__DETAIL__BILL__BUILDER_HPP_
#define TUTORIAL_INTERFACES__MSG__DETAIL__BILL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "tutorial_interfaces/msg/detail/bill__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace tutorial_interfaces
{

namespace msg
{

namespace builder
{

class Init_Bill_total
{
public:
  explicit Init_Bill_total(::tutorial_interfaces::msg::Bill & msg)
  : msg_(msg)
  {}
  ::tutorial_interfaces::msg::Bill total(::tutorial_interfaces::msg::Bill::_total_type arg)
  {
    msg_.total = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tutorial_interfaces::msg::Bill msg_;
};

class Init_Bill_price
{
public:
  explicit Init_Bill_price(::tutorial_interfaces::msg::Bill & msg)
  : msg_(msg)
  {}
  Init_Bill_total price(::tutorial_interfaces::msg::Bill::_price_type arg)
  {
    msg_.price = std::move(arg);
    return Init_Bill_total(msg_);
  }

private:
  ::tutorial_interfaces::msg::Bill msg_;
};

class Init_Bill_quantity
{
public:
  explicit Init_Bill_quantity(::tutorial_interfaces::msg::Bill & msg)
  : msg_(msg)
  {}
  Init_Bill_price quantity(::tutorial_interfaces::msg::Bill::_quantity_type arg)
  {
    msg_.quantity = std::move(arg);
    return Init_Bill_price(msg_);
  }

private:
  ::tutorial_interfaces::msg::Bill msg_;
};

class Init_Bill_timestamp
{
public:
  explicit Init_Bill_timestamp(::tutorial_interfaces::msg::Bill & msg)
  : msg_(msg)
  {}
  Init_Bill_quantity timestamp(::tutorial_interfaces::msg::Bill::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_Bill_quantity(msg_);
  }

private:
  ::tutorial_interfaces::msg::Bill msg_;
};

class Init_Bill_bill_number
{
public:
  Init_Bill_bill_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bill_timestamp bill_number(::tutorial_interfaces::msg::Bill::_bill_number_type arg)
  {
    msg_.bill_number = std::move(arg);
    return Init_Bill_timestamp(msg_);
  }

private:
  ::tutorial_interfaces::msg::Bill msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::tutorial_interfaces::msg::Bill>()
{
  return tutorial_interfaces::msg::builder::Init_Bill_bill_number();
}

}  // namespace tutorial_interfaces

#endif  // TUTORIAL_INTERFACES__MSG__DETAIL__BILL__BUILDER_HPP_
