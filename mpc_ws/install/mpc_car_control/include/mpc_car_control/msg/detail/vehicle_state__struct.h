// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mpc_car_control:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__STRUCT_H_
#define MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/VehicleState in the package mpc_car_control.
typedef struct mpc_car_control__msg__VehicleState
{
  double x;
  double y;
  double z;
  double roll;
  double pitch;
  double yaw;
  double vx;
  double vy;
  double vz;
  double roll_rate;
  double pitch_rate;
  double yaw_rate;
} mpc_car_control__msg__VehicleState;

// Struct for a sequence of mpc_car_control__msg__VehicleState.
typedef struct mpc_car_control__msg__VehicleState__Sequence
{
  mpc_car_control__msg__VehicleState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mpc_car_control__msg__VehicleState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__STRUCT_H_
