// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "mpc_car_control/msg/rosidl_typesupport_c__visibility_control.h"
#include "mpc_car_control/msg/detail/reference_trajectory__struct.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace mpc_car_control
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _ReferenceTrajectory_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ReferenceTrajectory_type_support_ids_t;

static const _ReferenceTrajectory_type_support_ids_t _ReferenceTrajectory_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ReferenceTrajectory_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ReferenceTrajectory_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ReferenceTrajectory_type_support_symbol_names_t _ReferenceTrajectory_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mpc_car_control, msg, ReferenceTrajectory)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mpc_car_control, msg, ReferenceTrajectory)),
  }
};

typedef struct _ReferenceTrajectory_type_support_data_t
{
  void * data[2];
} _ReferenceTrajectory_type_support_data_t;

static _ReferenceTrajectory_type_support_data_t _ReferenceTrajectory_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ReferenceTrajectory_message_typesupport_map = {
  2,
  "mpc_car_control",
  &_ReferenceTrajectory_message_typesupport_ids.typesupport_identifier[0],
  &_ReferenceTrajectory_message_typesupport_symbol_names.symbol_name[0],
  &_ReferenceTrajectory_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ReferenceTrajectory_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ReferenceTrajectory_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace mpc_car_control

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_C_EXPORT_mpc_car_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, mpc_car_control, msg, ReferenceTrajectory)() {
  return &::mpc_car_control::msg::rosidl_typesupport_c::ReferenceTrajectory_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
