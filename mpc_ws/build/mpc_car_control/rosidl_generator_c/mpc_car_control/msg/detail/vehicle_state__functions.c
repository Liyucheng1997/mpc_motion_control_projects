// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mpc_car_control:msg/VehicleState.idl
// generated code does not contain a copyright notice
#include "mpc_car_control/msg/detail/vehicle_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
mpc_car_control__msg__VehicleState__init(mpc_car_control__msg__VehicleState * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // z
  // roll
  // pitch
  // yaw
  // vx
  // vy
  // vz
  // roll_rate
  // pitch_rate
  // yaw_rate
  return true;
}

void
mpc_car_control__msg__VehicleState__fini(mpc_car_control__msg__VehicleState * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // z
  // roll
  // pitch
  // yaw
  // vx
  // vy
  // vz
  // roll_rate
  // pitch_rate
  // yaw_rate
}

bool
mpc_car_control__msg__VehicleState__are_equal(const mpc_car_control__msg__VehicleState * lhs, const mpc_car_control__msg__VehicleState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  // roll
  if (lhs->roll != rhs->roll) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // vx
  if (lhs->vx != rhs->vx) {
    return false;
  }
  // vy
  if (lhs->vy != rhs->vy) {
    return false;
  }
  // vz
  if (lhs->vz != rhs->vz) {
    return false;
  }
  // roll_rate
  if (lhs->roll_rate != rhs->roll_rate) {
    return false;
  }
  // pitch_rate
  if (lhs->pitch_rate != rhs->pitch_rate) {
    return false;
  }
  // yaw_rate
  if (lhs->yaw_rate != rhs->yaw_rate) {
    return false;
  }
  return true;
}

bool
mpc_car_control__msg__VehicleState__copy(
  const mpc_car_control__msg__VehicleState * input,
  mpc_car_control__msg__VehicleState * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  // roll
  output->roll = input->roll;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // vx
  output->vx = input->vx;
  // vy
  output->vy = input->vy;
  // vz
  output->vz = input->vz;
  // roll_rate
  output->roll_rate = input->roll_rate;
  // pitch_rate
  output->pitch_rate = input->pitch_rate;
  // yaw_rate
  output->yaw_rate = input->yaw_rate;
  return true;
}

mpc_car_control__msg__VehicleState *
mpc_car_control__msg__VehicleState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__VehicleState * msg = (mpc_car_control__msg__VehicleState *)allocator.allocate(sizeof(mpc_car_control__msg__VehicleState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mpc_car_control__msg__VehicleState));
  bool success = mpc_car_control__msg__VehicleState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mpc_car_control__msg__VehicleState__destroy(mpc_car_control__msg__VehicleState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mpc_car_control__msg__VehicleState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mpc_car_control__msg__VehicleState__Sequence__init(mpc_car_control__msg__VehicleState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__VehicleState * data = NULL;

  if (size) {
    data = (mpc_car_control__msg__VehicleState *)allocator.zero_allocate(size, sizeof(mpc_car_control__msg__VehicleState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mpc_car_control__msg__VehicleState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mpc_car_control__msg__VehicleState__fini(&data[i - 1]);
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
mpc_car_control__msg__VehicleState__Sequence__fini(mpc_car_control__msg__VehicleState__Sequence * array)
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
      mpc_car_control__msg__VehicleState__fini(&array->data[i]);
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

mpc_car_control__msg__VehicleState__Sequence *
mpc_car_control__msg__VehicleState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mpc_car_control__msg__VehicleState__Sequence * array = (mpc_car_control__msg__VehicleState__Sequence *)allocator.allocate(sizeof(mpc_car_control__msg__VehicleState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mpc_car_control__msg__VehicleState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mpc_car_control__msg__VehicleState__Sequence__destroy(mpc_car_control__msg__VehicleState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mpc_car_control__msg__VehicleState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mpc_car_control__msg__VehicleState__Sequence__are_equal(const mpc_car_control__msg__VehicleState__Sequence * lhs, const mpc_car_control__msg__VehicleState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mpc_car_control__msg__VehicleState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mpc_car_control__msg__VehicleState__Sequence__copy(
  const mpc_car_control__msg__VehicleState__Sequence * input,
  mpc_car_control__msg__VehicleState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mpc_car_control__msg__VehicleState);
    mpc_car_control__msg__VehicleState * data =
      (mpc_car_control__msg__VehicleState *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mpc_car_control__msg__VehicleState__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          mpc_car_control__msg__VehicleState__fini(&data[i]);
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
    if (!mpc_car_control__msg__VehicleState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
