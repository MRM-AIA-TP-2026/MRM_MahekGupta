// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_cashier_system:msg/Bill.idl
// generated code does not contain a copyright notice

#ifndef MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__BUILDER_HPP_
#define MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_cashier_system/msg/detail/bill__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_cashier_system
{

namespace msg
{


}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_cashier_system::msg::Bill>()
{
  return ::my_cashier_system::msg::Bill(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace my_cashier_system

#endif  // MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__BUILDER_HPP_
