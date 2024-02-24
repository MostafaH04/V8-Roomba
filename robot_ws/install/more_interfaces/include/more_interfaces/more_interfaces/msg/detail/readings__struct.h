// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from more_interfaces:msg/Readings.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__READINGS__STRUCT_H_
#define MORE_INTERFACES__MSG__DETAIL__READINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Readings in the package more_interfaces.
typedef struct more_interfaces__msg__Readings
{
  float acc_x;
  float acc_y;
  float acc_z;
  float gyr_x;
  float gyr_y;
  float gyr_z;
  float temp;
} more_interfaces__msg__Readings;

// Struct for a sequence of more_interfaces__msg__Readings.
typedef struct more_interfaces__msg__Readings__Sequence
{
  more_interfaces__msg__Readings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} more_interfaces__msg__Readings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MORE_INTERFACES__MSG__DETAIL__READINGS__STRUCT_H_
