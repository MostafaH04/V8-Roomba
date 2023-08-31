// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from more_interfaces:msg/Controls.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__CONTROLS__STRUCT_H_
#define MORE_INTERFACES__MSG__DETAIL__CONTROLS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Controls in the package more_interfaces.
typedef struct more_interfaces__msg__Controls
{
  float speed;
  float steering;
} more_interfaces__msg__Controls;

// Struct for a sequence of more_interfaces__msg__Controls.
typedef struct more_interfaces__msg__Controls__Sequence
{
  more_interfaces__msg__Controls * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} more_interfaces__msg__Controls__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MORE_INTERFACES__MSG__DETAIL__CONTROLS__STRUCT_H_
