// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_cashier_system:msg/Bill.idl
// generated code does not contain a copyright notice

#ifndef MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__TRAITS_HPP_
#define MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_cashier_system/msg/detail/bill__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace my_cashier_system
{

namespace msg
{

inline void to_flow_style_yaml(
  const Bill & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Bill & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Bill & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace my_cashier_system

namespace rosidl_generator_traits
{

[[deprecated("use my_cashier_system::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_cashier_system::msg::Bill & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_cashier_system::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_cashier_system::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_cashier_system::msg::Bill & msg)
{
  return my_cashier_system::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_cashier_system::msg::Bill>()
{
  return "my_cashier_system::msg::Bill";
}

template<>
inline const char * name<my_cashier_system::msg::Bill>()
{
  return "my_cashier_system/msg/Bill";
}

template<>
struct has_fixed_size<my_cashier_system::msg::Bill>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_cashier_system::msg::Bill>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_cashier_system::msg::Bill>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__TRAITS_HPP_
