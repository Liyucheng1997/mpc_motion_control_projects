// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mpc_car_control:msg/ControlCommandBody.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__STRUCT_H_
#define MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

// Struct defined in msg/ControlCommandBody in the package mpc_car_control.
typedef struct mpc_car_control__msg__ControlCommandBody
{
  std_msgs__msg__Header header;
  double fx;
  double fy;
  double mz;
} mpc_car_control__msg__ControlCommandBody;

// Struct for a sequence of mpc_car_control__msg__ControlCommandBody.
typedef struct mpc_car_control__msg__ControlCommandBody__Sequence
{
  mpc_car_control__msg__ControlCommandBody * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mpc_car_control__msg__ControlCommandBody__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__STRUCT_H_
