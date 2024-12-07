// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_cashier_system:msg/Bill.idl
// generated code does not contain a copyright notice
#include "my_cashier_system/msg/detail/bill__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
my_cashier_system__msg__Bill__init(my_cashier_system__msg__Bill * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
my_cashier_system__msg__Bill__fini(my_cashier_system__msg__Bill * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
my_cashier_system__msg__Bill__are_equal(const my_cashier_system__msg__Bill * lhs, const my_cashier_system__msg__Bill * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
my_cashier_system__msg__Bill__copy(
  const my_cashier_system__msg__Bill * input,
  my_cashier_system__msg__Bill * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

my_cashier_system__msg__Bill *
my_cashier_system__msg__Bill__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_cashier_system__msg__Bill * msg = (my_cashier_system__msg__Bill *)allocator.allocate(sizeof(my_cashier_system__msg__Bill), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_cashier_system__msg__Bill));
  bool success = my_cashier_system__msg__Bill__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_cashier_system__msg__Bill__destroy(my_cashier_system__msg__Bill * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_cashier_system__msg__Bill__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_cashier_system__msg__Bill__Sequence__init(my_cashier_system__msg__Bill__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_cashier_system__msg__Bill * data = NULL;

  if (size) {
    data = (my_cashier_system__msg__Bill *)allocator.zero_allocate(size, sizeof(my_cashier_system__msg__Bill), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_cashier_system__msg__Bill__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_cashier_system__msg__Bill__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
my_cashier_system__msg__Bill__Sequence__fini(my_cashier_system__msg__Bill__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      my_cashier_system__msg__Bill__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

my_cashier_system__msg__Bill__Sequence *
my_cashier_system__msg__Bill__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_cashier_system__msg__Bill__Sequence * array = (my_cashier_system__msg__Bill__Sequence *)allocator.allocate(sizeof(my_cashier_system__msg__Bill__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_cashier_system__msg__Bill__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_cashier_system__msg__Bill__Sequence__destroy(my_cashier_system__msg__Bill__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_cashier_system__msg__Bill__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_cashier_system__msg__Bill__Sequence__are_equal(const my_cashier_system__msg__Bill__Sequence * lhs, const my_cashier_system__msg__Bill__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_cashier_system__msg__Bill__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_cashier_system__msg__Bill__Sequence__copy(
  const my_cashier_system__msg__Bill__Sequence * input,
  my_cashier_system__msg__Bill__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_cashier_system__msg__Bill);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_cashier_system__msg__Bill * data =
      (my_cashier_system__msg__Bill *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_cashier_system__msg__Bill__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_cashier_system__msg__Bill__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_cashier_system__msg__Bill__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
