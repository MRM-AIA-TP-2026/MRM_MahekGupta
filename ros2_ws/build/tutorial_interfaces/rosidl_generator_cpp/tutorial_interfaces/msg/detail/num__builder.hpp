// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tutorial_interfaces:msg/Num.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__MSG__DETAIL__NUM__BUILDER_HPP_
#define TUTORIAL_INTERFACES__MSG__DETAIL__NUM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "tutorial_interfaces/msg/detail/num__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace tutorial_interfaces
{

namespace msg
{

namespace builder
{

class Init_Num_total
{
public:
  explicit Init_Num_total(::tutorial_interfaces::msg::Num & msg)
  : msg_(msg)
  {}
  ::tutorial_interfaces::msg::Num total(::tutorial_interfaces::msg::Num::_total_type arg)
  {
    msg_.total = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tutorial_interfaces::msg::Num msg_;
};

class Init_Num_price
{
public:
  explicit Init_Num_price(::tutorial_interfaces::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_total price(::tutorial_interfaces::msg::Num::_price_type arg)
  {
    msg_.price = std::move(arg);
    return Init_Num_total(msg_);
  }

private:
  ::tutorial_interfaces::msg::Num msg_;
};

class Init_Num_quantity
{
public:
  explicit Init_Num_quantity(::tutorial_interfaces::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_price quantity(::tutorial_interfaces::msg::Num::_quantity_type arg)
  {
    msg_.quantity = std::move(arg);
    return Init_Num_price(msg_);
  }

private:
  ::tutorial_interfaces::msg::Num msg_;
};

class Init_Num_timestamp
{
public:
  explicit Init_Num_timestamp(::tutorial_interfaces::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_quantity timestamp(::tutorial_interfaces::msg::Num::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_Num_quantity(msg_);
  }

private:
  ::tutorial_interfaces::msg::Num msg_;
};

class Init_Num_bill_number
{
public:
  Init_Num_bill_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Num_timestamp bill_number(::tutorial_interfaces::msg::Num::_bill_number_type arg)
  {
    msg_.bill_number = std::move(arg);
    return Init_Num_timestamp(msg_);
  }

private:
  ::tutorial_interfaces::msg::Num msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::tutorial_interfaces::msg::Num>()
{
  return tutorial_interfaces::msg::builder::Init_Num_bill_number();
}

}  // namespace tutorial_interfaces

#endif  // TUTORIAL_INTERFACES__MSG__DETAIL__NUM__BUILDER_HPP_
