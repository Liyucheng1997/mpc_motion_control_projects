// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice
#include "mpc_car_control/msg/detail/reference_trajectory__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `points`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `velocity_profile`
// Member `yaw_profile`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
mpc_car_control__msg__ReferenceTrajectory__init(mpc_car_control__msg__ReferenceTrajectory * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    mpc_car_control__msg__ReferenceTrajectory__fini(msg);
    return false;
  }
  // points
  if (!geometry_msgs__msg__Point__Sequence__init(&msg->points, 0)) {
    mpc_car_control__msg__ReferenceTrajectory__fini(msg);
    return false;
  }
  // velocity_profile
  if (!rosidl_runtime_c__double__Sequence__init(&msg->velocity_profile, 0)) {
    mpc_car_control__msg__ReferenceTrajectory__fini(msg);
    return false;
  }
  // yaw_profile
  if (!rosidl_runtime_c__double__Sequence__init(&msg->yaw_profile, 0)) {
    mpc_car_control__msg__ReferenceTrajectory__fini(msg);
    return false;
  }
  return true;
}

void
mpc_car_control__msg__ReferenceTrajectory__fini(mpc_car_control__msg__ReferenceTrajectory * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // points
  geometry_msgs__msg__Point__Sequence__fini(&msg->points);
  // velocity_profile
  rosidl_runtime_c__double__Sequence__fini(&msg->velocity_profile);
  // yaw_profile
  rosidl_runtime_c__double__Sequence__fini(&msg->yaw_profile);
}

bool
mpc_car_control__msg__ReferenceTrajectory__are_equal(const mpc_car_control__msg__ReferenceTrajectory * lhs, const mpc_car_control__msg__ReferenceTrajectory * rhs)
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
  // points
  if (!geometry_msgs__msg__Point__Sequence__are_equal(
      &(lhs->points), &(rhs->points)))
  {
    return false;
  }
  // velocity_profile
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->velocity_profile), &(rhs->velocity_profile)))
  {
    return false;
  }
  // yaw_profile
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->yaw_profile), &(rhs->yaw_profile)))
  {
    return false;
  }
  return true;
}

bool
mpc_car_control__msg__ReferenceTrajectory__copy(
  const mpc_car_control__msg__ReferenceTrajectory * input,
  mpc_car_control__msg__ReferenceTrajectory * output)
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
  // points
  if (!geometry_msgs__msg__Point__Sequence__copy(
      &(input->points), &(output->points)))
  {
    return false;
  }
  // velocity_profile
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->velocity_profile), &(output->velocity_profile)))
  {
    return false;
  }
  // yaw_profile
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->yaw_profile), &(output->yaw_profile)))
  {
    return false;
  }
  return true;
}

mpc_car_control__msg__ReferenceTrajectory *
mpc_car_control__msg__ReferenceTrajectory__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__ReferenceTrajectory * msg = (mpc_car_control__msg__ReferenceTrajectory *)allocator.allocate(sizeof(mpc_car_control__msg__ReferenceTrajectory), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mpc_car_control__msg__ReferenceTrajectory));
  bool success = mpc_car_control__msg__ReferenceTrajectory__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mpc_car_control__msg__ReferenceTrajectory__destroy(mpc_car_control__msg__ReferenceTrajectory * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mpc_car_control__msg__ReferenceTrajectory__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mpc_car_control__msg__ReferenceTrajectory__Sequence__init(mpc_car_control__msg__ReferenceTrajectory__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__ReferenceTrajectory * data = NULL;

  if (size) {
    data = (mpc_car_control__msg__ReferenceTrajectory *)allocator.zero_allocate(size, sizeof(mpc_car_control__msg__ReferenceTrajectory), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mpc_car_control__msg__ReferenceTrajectory__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mpc_car_control__msg__ReferenceTrajectory__fini(&data[i - 1]);
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
mpc_car_control__msg__ReferenceTrajectory__Sequence__fini(mpc_car_control__msg__ReferenceTrajectory__Sequence * array)
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
      mpc_car_control__msg__ReferenceTrajectory__fini(&array->data[i]);
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

mpc_car_control__msg__ReferenceTrajectory__Sequence *
mpc_car_control__msg__ReferenceTrajectory__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__ReferenceTrajectory__Sequence * array = (mpc_car_control__msg__ReferenceTrajectory__Sequence *)allocator.allocate(sizeof(mpc_car_control__msg__ReferenceTrajectory__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mpc_car_control__msg__ReferenceTrajectory__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mpc_car_control__msg__ReferenceTrajectory__Sequence__destroy(mpc_car_control__msg__ReferenceTrajectory__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mpc_car_control__msg__ReferenceTrajectory__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mpc_car_control__msg__ReferenceTrajectory__Sequence__are_equal(const mpc_car_control__msg__ReferenceTrajectory__Sequence * lhs, const mpc_car_control__msg__ReferenceTrajectory__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mpc_car_control__msg__ReferenceTrajectory__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mpc_car_control__msg__ReferenceTrajectory__Sequence__copy(
  const mpc_car_control__msg__ReferenceTrajectory__Sequence * input,
  mpc_car_control__msg__ReferenceTrajectory__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mpc_car_control__msg__ReferenceTrajectory);
    mpc_car_control__msg__ReferenceTrajectory * data =
      (mpc_car_control__msg__ReferenceTrajectory *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mpc_car_control__msg__ReferenceTrajectory__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          mpc_car_control__msg__ReferenceTrajectory__fini(&data[i]);
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
    if (!mpc_car_control__msg__ReferenceTrajectory__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
