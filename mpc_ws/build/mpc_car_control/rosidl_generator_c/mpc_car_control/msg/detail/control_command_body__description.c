// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from mpc_car_control:msg/ControlCommandBody.idl
// generated code does not contain a copyright notice

#include "mpc_car_control/msg/detail/control_command_body__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_mpc_car_control
const rosidl_type_hash_t *
mpc_car_control__msg__ControlCommandBody__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2b, 0x89, 0x13, 0xf3, 0xbd, 0x91, 0xd4, 0x8f,
      0x0e, 0x69, 0x13, 0x4f, 0x97, 0x7e, 0x21, 0x53,
      0x71, 0xe7, 0xbe, 0xd1, 0x47, 0xbf, 0x74, 0xe3,
      0x34, 0xbe, 0x17, 0x31, 0x18, 0xec, 0x2a, 0xdc,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "std_msgs/msg/detail/header__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char mpc_car_control__msg__ControlCommandBody__TYPE_NAME[] = "mpc_car_control/msg/ControlCommandBody";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__header[] = "header";
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__fx[] = "fx";
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__fy[] = "fy";
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__mz[] = "mz";
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__fz[] = "fz";
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__mx[] = "mx";
static char mpc_car_control__msg__ControlCommandBody__FIELD_NAME__my[] = "my";

static rosidl_runtime_c__type_description__Field mpc_car_control__msg__ControlCommandBody__FIELDS[] = {
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__fx, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__fy, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__mz, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__fz, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__mx, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mpc_car_control__msg__ControlCommandBody__FIELD_NAME__my, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription mpc_car_control__msg__ControlCommandBody__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mpc_car_control__msg__ControlCommandBody__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mpc_car_control__msg__ControlCommandBody__TYPE_NAME, 38, 38},
      {mpc_car_control__msg__ControlCommandBody__FIELDS, 7, 7},
    },
    {mpc_car_control__msg__ControlCommandBody__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "std_msgs/Header header\n"
  "float64 fx\n"
  "float64 fy\n"
  "float64 mz\n"
  "float64 fz\n"
  "float64 mx\n"
  "float64 my";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
mpc_car_control__msg__ControlCommandBody__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mpc_car_control__msg__ControlCommandBody__TYPE_NAME, 38, 38},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 89, 89},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mpc_car_control__msg__ControlCommandBody__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mpc_car_control__msg__ControlCommandBody__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
