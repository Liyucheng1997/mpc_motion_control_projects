// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from mpc_car_control:msg/WheelGroundHeights.idl
// generated code does not contain a copyright notice
#include "mpc_car_control/msg/detail/wheel_ground_heights__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "mpc_car_control/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "mpc_car_control/msg/detail/wheel_ground_heights__struct.h"
#include "mpc_car_control/msg/detail/wheel_ground_heights__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _WheelGroundHeights__ros_msg_type = mpc_car_control__msg__WheelGroundHeights;

static bool _WheelGroundHeights__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _WheelGroundHeights__ros_msg_type * ros_message = static_cast<const _WheelGroundHeights__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: wheel_ground_heights
  {
    size_t size = 4;
    auto array_ptr = ros_message->wheel_ground_heights;
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _WheelGroundHeights__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _WheelGroundHeights__ros_msg_type * ros_message = static_cast<_WheelGroundHeights__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: wheel_ground_heights
  {
    size_t size = 4;
    auto array_ptr = ros_message->wheel_ground_heights;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t get_serialized_size_mpc_car_control__msg__WheelGroundHeights(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _WheelGroundHeights__ros_msg_type * ros_message = static_cast<const _WheelGroundHeights__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name wheel_ground_heights
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->wheel_ground_heights;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _WheelGroundHeights__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_mpc_car_control__msg__WheelGroundHeights(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t max_serialized_size_mpc_car_control__msg__WheelGroundHeights(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Header(
        full_bounded, current_alignment);
    }
  }
  // member: wheel_ground_heights
  {
    size_t array_size = 4;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _WheelGroundHeights__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_mpc_car_control__msg__WheelGroundHeights(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_WheelGroundHeights = {
  "mpc_car_control::msg",
  "WheelGroundHeights",
  _WheelGroundHeights__cdr_serialize,
  _WheelGroundHeights__cdr_deserialize,
  _WheelGroundHeights__get_serialized_size,
  _WheelGroundHeights__max_serialized_size
};

static rosidl_message_type_support_t _WheelGroundHeights__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_WheelGroundHeights,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mpc_car_control, msg, WheelGroundHeights)() {
  return &_WheelGroundHeights__type_support;
}

#if defined(__cplusplus)
}
#endif
