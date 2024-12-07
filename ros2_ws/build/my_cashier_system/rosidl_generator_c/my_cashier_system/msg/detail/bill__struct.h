// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_cashier_system:msg/Bill.idl
// generated code does not contain a copyright notice

#ifndef MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__STRUCT_H_
#define MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Bill in the package my_cashier_system.
typedef struct my_cashier_system__msg__Bill
{
  uint8_t structure_needs_at_least_one_member;
} my_cashier_system__msg__Bill;

// Struct for a sequence of my_cashier_system__msg__Bill.
typedef struct my_cashier_system__msg__Bill__Sequence
{
  my_cashier_system__msg__Bill * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_cashier_system__msg__Bill__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_CASHIER_SYSTEM__MSG__DETAIL__BILL__STRUCT_H_
