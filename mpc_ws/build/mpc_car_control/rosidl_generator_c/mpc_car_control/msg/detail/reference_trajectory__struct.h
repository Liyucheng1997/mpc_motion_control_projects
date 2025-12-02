// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__STRUCT_H_
#define MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__STRUCT_H_

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
// Member 'points'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velocity_profile'
// Member 'yaw_profile'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/ReferenceTrajectory in the package mpc_car_control.
typedef struct mpc_car_control__msg__ReferenceTrajectory
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__Point__Sequence points;
  rosidl_runtime_c__double__Sequence velocity_profile;
  rosidl_runtime_c__double__Sequence yaw_profile;
} mpc_car_control__msg__ReferenceTrajectory;

// Struct for a sequence of mpc_car_control__msg__ReferenceTrajectory.
typedef struct mpc_car_control__msg__ReferenceTrajectory__Sequence
{
  mpc_car_control__msg__ReferenceTrajectory * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mpc_car_control__msg__ReferenceTrajectory__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__STRUCT_H_
