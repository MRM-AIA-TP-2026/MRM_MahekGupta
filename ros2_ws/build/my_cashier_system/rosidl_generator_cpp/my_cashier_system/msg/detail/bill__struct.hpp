// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_cashier_system:msg/Bill.idl
// generated code does not contain a copyright notice

#ifndef MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__STRUCT_HPP_
#define MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__my_cashier_system__msg__Bill __attribute__((deprecated))
#else
# define DEPRECATED__my_cashier_system__msg__Bill __declspec(deprecated)
#endif

namespace my_cashier_system
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Bill_
{
  using Type = Bill_<ContainerAllocator>;

  explicit Bill_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit Bill_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    my_cashier_system::msg::Bill_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_cashier_system::msg::Bill_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_cashier_system::msg::Bill_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_cashier_system::msg::Bill_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_cashier_system::msg::Bill_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_cashier_system::msg::Bill_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_cashier_system::msg::Bill_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_cashier_system::msg::Bill_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_cashier_system::msg::Bill_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_cashier_system::msg::Bill_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_cashier_system__msg__Bill
    std::shared_ptr<my_cashier_system::msg::Bill_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_cashier_system__msg__Bill
    std::shared_ptr<my_cashier_system::msg::Bill_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Bill_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const Bill_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Bill_

// alias to use template instance with default allocator
using Bill =
  my_cashier_system::msg::Bill_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_cashier_system

#endif  // MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__STRUCT_HPP_
