// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from tutorial_interfaces:msg/Bill.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__MSG__DETAIL__BILL__STRUCT_H_
#define TUTORIAL_INTERFACES__MSG__DETAIL__BILL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/Bill in the package tutorial_interfaces.
typedef struct tutorial_interfaces__msg__Bill
{
  uint32_t bill_number;
  builtin_interfaces__msg__Time timestamp;
  float quantity;
  float price;
  float total;
} tutorial_interfaces__msg__Bill;

// Struct for a sequence of tutorial_interfaces__msg__Bill.
typedef struct tutorial_interfaces__msg__Bill__Sequence
{
  tutorial_interfaces__msg__Bill * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tutorial_interfaces__msg__Bill__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TUTORIAL_INTERFACES__MSG__DETAIL__BILL__STRUCT_H_
