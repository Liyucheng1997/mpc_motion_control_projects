// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from mpc_car_control:msg/ActuatorCommand.idl
// generated code does not contain a copyright notice
#include "mpc_car_control/msg/detail/actuator_command__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "mpc_car_control/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "mpc_car_control/msg/detail/actuator_command__struct.h"
#include "mpc_car_control/msg/detail/actuator_command__functions.h"
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
bool cdr_serialize_std_msgs__msg__Header(
  const std_msgs__msg__Header * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
bool cdr_deserialize_std_msgs__msg__Header(
  eprosima::fastcdr::Cdr & cdr,
  std_msgs__msg__Header * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
bool cdr_serialize_key_std_msgs__msg__Header(
  const std_msgs__msg__Header * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
size_t get_serialized_size_key_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
size_t max_serialized_size_key_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mpc_car_control
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _ActuatorCommand__ros_msg_type = mpc_car_control__msg__ActuatorCommand;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
bool cdr_serialize_mpc_car_control__msg__ActuatorCommand(
  const mpc_car_control__msg__ActuatorCommand * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: header
  {
    cdr_serialize_std_msgs__msg__Header(
      &ros_message->header, cdr);
  }

  // Field name: steering_angle
  {
    cdr << ros_message->steering_angle;
  }

  // Field name: throttle
  {
    cdr << ros_message->throttle;
  }

  // Field name: brake
  {
    cdr << ros_message->brake;
  }

  // Field name: active_suspension_force
  {
    size_t size = 4;
    auto array_ptr = ros_message->active_suspension_force;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: wheel_torque
  {
    size_t size = 4;
    auto array_ptr = ros_message->wheel_torque;
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
bool cdr_deserialize_mpc_car_control__msg__ActuatorCommand(
  eprosima::fastcdr::Cdr & cdr,
  mpc_car_control__msg__ActuatorCommand * ros_message)
{
  // Field name: header
  {
    cdr_deserialize_std_msgs__msg__Header(cdr, &ros_message->header);
  }

  // Field name: steering_angle
  {
    cdr >> ros_message->steering_angle;
  }

  // Field name: throttle
  {
    cdr >> ros_message->throttle;
  }

  // Field name: brake
  {
    cdr >> ros_message->brake;
  }

  // Field name: active_suspension_force
  {
    size_t size = 4;
    auto array_ptr = ros_message->active_suspension_force;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: wheel_torque
  {
    size_t size = 4;
    auto array_ptr = ros_message->wheel_torque;
    cdr.deserialize_array(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t get_serialized_size_mpc_car_control__msg__ActuatorCommand(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ActuatorCommand__ros_msg_type * ros_message = static_cast<const _ActuatorCommand__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: header
  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);

  // Field name: steering_angle
  {
    size_t item_size = sizeof(ros_message->steering_angle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: throttle
  {
    size_t item_size = sizeof(ros_message->throttle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: brake
  {
    size_t item_size = sizeof(ros_message->brake);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: active_suspension_force
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->active_suspension_force;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: wheel_torque
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->wheel_torque;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t max_serialized_size_mpc_car_control__msg__ActuatorCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: header
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: steering_angle
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: throttle
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: brake
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: active_suspension_force
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: wheel_torque
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = mpc_car_control__msg__ActuatorCommand;
    is_plain =
      (
      offsetof(DataType, wheel_torque) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
bool cdr_serialize_key_mpc_car_control__msg__ActuatorCommand(
  const mpc_car_control__msg__ActuatorCommand * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: header
  {
    cdr_serialize_key_std_msgs__msg__Header(
      &ros_message->header, cdr);
  }

  // Field name: steering_angle
  {
    cdr << ros_message->steering_angle;
  }

  // Field name: throttle
  {
    cdr << ros_message->throttle;
  }

  // Field name: brake
  {
    cdr << ros_message->brake;
  }

  // Field name: active_suspension_force
  {
    size_t size = 4;
    auto array_ptr = ros_message->active_suspension_force;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: wheel_torque
  {
    size_t size = 4;
    auto array_ptr = ros_message->wheel_torque;
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t get_serialized_size_key_mpc_car_control__msg__ActuatorCommand(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ActuatorCommand__ros_msg_type * ros_message = static_cast<const _ActuatorCommand__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: header
  current_alignment += get_serialized_size_key_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);

  // Field name: steering_angle
  {
    size_t item_size = sizeof(ros_message->steering_angle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: throttle
  {
    size_t item_size = sizeof(ros_message->throttle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: brake
  {
    size_t item_size = sizeof(ros_message->brake);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: active_suspension_force
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->active_suspension_force;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: wheel_torque
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->wheel_torque;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t max_serialized_size_key_mpc_car_control__msg__ActuatorCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: header
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: steering_angle
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: throttle
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: brake
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: active_suspension_force
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: wheel_torque
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = mpc_car_control__msg__ActuatorCommand;
    is_plain =
      (
      offsetof(DataType, wheel_torque) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _ActuatorCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const mpc_car_control__msg__ActuatorCommand * ros_message = static_cast<const mpc_car_control__msg__ActuatorCommand *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_mpc_car_control__msg__ActuatorCommand(ros_message, cdr);
}

static bool _ActuatorCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  mpc_car_control__msg__ActuatorCommand * ros_message = static_cast<mpc_car_control__msg__ActuatorCommand *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_mpc_car_control__msg__ActuatorCommand(cdr, ros_message);
}

static uint32_t _ActuatorCommand__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_mpc_car_control__msg__ActuatorCommand(
      untyped_ros_message, 0));
}

static size_t _ActuatorCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_mpc_car_control__msg__ActuatorCommand(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ActuatorCommand = {
  "mpc_car_control::msg",
  "ActuatorCommand",
  _ActuatorCommand__cdr_serialize,
  _ActuatorCommand__cdr_deserialize,
  _ActuatorCommand__get_serialized_size,
  _ActuatorCommand__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _ActuatorCommand__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ActuatorCommand,
  get_message_typesupport_handle_function,
  &mpc_car_control__msg__ActuatorCommand__get_type_hash,
  &mpc_car_control__msg__ActuatorCommand__get_type_description,
  &mpc_car_control__msg__ActuatorCommand__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mpc_car_control, msg, ActuatorCommand)() {
  return &_ActuatorCommand__type_support;
}

#if defined(__cplusplus)
}
#endif
