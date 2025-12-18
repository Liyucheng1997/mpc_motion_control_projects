// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mpc_car_control:msg/WheelGroundHeights.idl
// generated code does not contain a copyright notice
#include "mpc_car_control/msg/detail/wheel_ground_heights__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
mpc_car_control__msg__WheelGroundHeights__init(mpc_car_control__msg__WheelGroundHeights * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    mpc_car_control__msg__WheelGroundHeights__fini(msg);
    return false;
  }
  // wheel_ground_heights
  return true;
}

void
mpc_car_control__msg__WheelGroundHeights__fini(mpc_car_control__msg__WheelGroundHeights * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // wheel_ground_heights
}

bool
mpc_car_control__msg__WheelGroundHeights__are_equal(const mpc_car_control__msg__WheelGroundHeights * lhs, const mpc_car_control__msg__WheelGroundHeights * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // wheel_ground_heights
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->wheel_ground_heights[i] != rhs->wheel_ground_heights[i]) {
      return false;
    }
  }
  return true;
}

bool
mpc_car_control__msg__WheelGroundHeights__copy(
  const mpc_car_control__msg__WheelGroundHeights * input,
  mpc_car_control__msg__WheelGroundHeights * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // wheel_ground_heights
  for (size_t i = 0; i < 4; ++i) {
    output->wheel_ground_heights[i] = input->wheel_ground_heights[i];
  }
  return true;
}

mpc_car_control__msg__WheelGroundHeights *
mpc_car_control__msg__WheelGroundHeights__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__WheelGroundHeights * msg = (mpc_car_control__msg__WheelGroundHeights *)allocator.allocate(sizeof(mpc_car_control__msg__WheelGroundHeights), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mpc_car_control__msg__WheelGroundHeights));
  bool success = mpc_car_control__msg__WheelGroundHeights__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mpc_car_control__msg__WheelGroundHeights__destroy(mpc_car_control__msg__WheelGroundHeights * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mpc_car_control__msg__WheelGroundHeights__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mpc_car_control__msg__WheelGroundHeights__Sequence__init(mpc_car_control__msg__WheelGroundHeights__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__WheelGroundHeights * data = NULL;

  if (size) {
    data = (mpc_car_control__msg__WheelGroundHeights *)allocator.zero_allocate(size, sizeof(mpc_car_control__msg__WheelGroundHeights), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mpc_car_control__msg__WheelGroundHeights__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mpc_car_control__msg__WheelGroundHeights__fini(&data[i - 1]);
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
mpc_car_control__msg__WheelGroundHeights__Sequence__fini(mpc_car_control__msg__WheelGroundHeights__Sequence * array)
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
      mpc_car_control__msg__WheelGroundHeights__fini(&array->data[i]);
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

mpc_car_control__msg__WheelGroundHeights__Sequence *
mpc_car_control__msg__WheelGroundHeights__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__WheelGroundHeights__Sequence * array = (mpc_car_control__msg__WheelGroundHeights__Sequence *)allocator.allocate(sizeof(mpc_car_control__msg__WheelGroundHeights__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mpc_car_control__msg__WheelGroundHeights__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mpc_car_control__msg__WheelGroundHeights__Sequence__destroy(mpc_car_control__msg__WheelGroundHeights__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mpc_car_control__msg__WheelGroundHeights__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mpc_car_control__msg__WheelGroundHeights__Sequence__are_equal(const mpc_car_control__msg__WheelGroundHeights__Sequence * lhs, const mpc_car_control__msg__WheelGroundHeights__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mpc_car_control__msg__WheelGroundHeights__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mpc_car_control__msg__WheelGroundHeights__Sequence__copy(
  const mpc_car_control__msg__WheelGroundHeights__Sequence * input,
  mpc_car_control__msg__WheelGroundHeights__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mpc_car_control__msg__WheelGroundHeights);
    mpc_car_control__msg__WheelGroundHeights * data =
      (mpc_car_control__msg__WheelGroundHeights *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mpc_car_control__msg__WheelGroundHeights__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          mpc_car_control__msg__WheelGroundHeights__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!mpc_car_control__msg__WheelGroundHeights__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
