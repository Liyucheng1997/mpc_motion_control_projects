// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from mpc_car_control:msg/ControlCommandBody.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__FUNCTIONS_H_
#define MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "mpc_car_control/msg/rosidl_generator_c__visibility_control.h"

#include "mpc_car_control/msg/detail/control_command_body__struct.h"

/// Initialize msg/ControlCommandBody message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * mpc_car_control__msg__ControlCommandBody
 * )) before or use
 * mpc_car_control__msg__ControlCommandBody__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
bool
mpc_car_control__msg__ControlCommandBody__init(mpc_car_control__msg__ControlCommandBody * msg);

/// Finalize msg/ControlCommandBody message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
void
mpc_car_control__msg__ControlCommandBody__fini(mpc_car_control__msg__ControlCommandBody * msg);

/// Create msg/ControlCommandBody message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * mpc_car_control__msg__ControlCommandBody__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
mpc_car_control__msg__ControlCommandBody *
mpc_car_control__msg__ControlCommandBody__create();

/// Destroy msg/ControlCommandBody message.
/**
 * It calls
 * mpc_car_control__msg__ControlCommandBody__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
void
mpc_car_control__msg__ControlCommandBody__destroy(mpc_car_control__msg__ControlCommandBody * msg);

/// Check for msg/ControlCommandBody message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
bool
mpc_car_control__msg__ControlCommandBody__are_equal(const mpc_car_control__msg__ControlCommandBody * lhs, const mpc_car_control__msg__ControlCommandBody * rhs);

/// Copy a msg/ControlCommandBody message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
bool
mpc_car_control__msg__ControlCommandBody__copy(
  const mpc_car_control__msg__ControlCommandBody * input,
  mpc_car_control__msg__ControlCommandBody * output);

/// Initialize array of msg/ControlCommandBody messages.
/**
 * It allocates the memory for the number of elements and calls
 * mpc_car_control__msg__ControlCommandBody__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
bool
mpc_car_control__msg__ControlCommandBody__Sequence__init(mpc_car_control__msg__ControlCommandBody__Sequence * array, size_t size);

/// Finalize array of msg/ControlCommandBody messages.
/**
 * It calls
 * mpc_car_control__msg__ControlCommandBody__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
void
mpc_car_control__msg__ControlCommandBody__Sequence__fini(mpc_car_control__msg__ControlCommandBody__Sequence * array);

/// Create array of msg/ControlCommandBody messages.
/**
 * It allocates the memory for the array and calls
 * mpc_car_control__msg__ControlCommandBody__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
mpc_car_control__msg__ControlCommandBody__Sequence *
mpc_car_control__msg__ControlCommandBody__Sequence__create(size_t size);

/// Destroy array of msg/ControlCommandBody messages.
/**
 * It calls
 * mpc_car_control__msg__ControlCommandBody__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
void
mpc_car_control__msg__ControlCommandBody__Sequence__destroy(mpc_car_control__msg__ControlCommandBody__Sequence * array);

/// Check for msg/ControlCommandBody message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
bool
mpc_car_control__msg__ControlCommandBody__Sequence__are_equal(const mpc_car_control__msg__ControlCommandBody__Sequence * lhs, const mpc_car_control__msg__ControlCommandBody__Sequence * rhs);

/// Copy an array of msg/ControlCommandBody messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
bool
mpc_car_control__msg__ControlCommandBody__Sequence__copy(
  const mpc_car_control__msg__ControlCommandBody__Sequence * input,
  mpc_car_control__msg__ControlCommandBody__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__FUNCTIONS_H_
