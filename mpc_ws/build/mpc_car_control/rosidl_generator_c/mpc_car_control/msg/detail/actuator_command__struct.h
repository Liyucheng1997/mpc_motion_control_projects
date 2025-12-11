// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mpc_car_control:msg/ActuatorCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/actuator_command.h"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__STRUCT_H_
#define MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__STRUCT_H_

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

/// Struct defined in msg/ActuatorCommand in the package mpc_car_control.
typedef struct mpc_car_control__msg__ActuatorCommand
{
  std_msgs__msg__Header header;
  double steering_angle;
  double throttle;
  double brake;
  double active_suspension_force[4];
} mpc_car_control__msg__ActuatorCommand;

// Struct for a sequence of mpc_car_control__msg__ActuatorCommand.
typedef struct mpc_car_control__msg__ActuatorCommand__Sequence
{
  mpc_car_control__msg__ActuatorCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mpc_car_control__msg__ActuatorCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__STRUCT_H_
