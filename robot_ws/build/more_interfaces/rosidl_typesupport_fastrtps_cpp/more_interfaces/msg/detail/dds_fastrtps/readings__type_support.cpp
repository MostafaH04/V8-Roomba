// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from more_interfaces:msg/Readings.idl
// generated code does not contain a copyright notice
#include "more_interfaces/msg/detail/readings__rosidl_typesupport_fastrtps_cpp.hpp"
#include "more_interfaces/msg/detail/readings__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace more_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_more_interfaces
cdr_serialize(
  const more_interfaces::msg::Readings & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: acc_x
  cdr << ros_message.acc_x;
  // Member: acc_y
  cdr << ros_message.acc_y;
  // Member: acc_z
  cdr << ros_message.acc_z;
  // Member: gyr_x
  cdr << ros_message.gyr_x;
  // Member: gyr_y
  cdr << ros_message.gyr_y;
  // Member: gyr_z
  cdr << ros_message.gyr_z;
  // Member: temp
  cdr << ros_message.temp;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_more_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  more_interfaces::msg::Readings & ros_message)
{
  // Member: acc_x
  cdr >> ros_message.acc_x;

  // Member: acc_y
  cdr >> ros_message.acc_y;

  // Member: acc_z
  cdr >> ros_message.acc_z;

  // Member: gyr_x
  cdr >> ros_message.gyr_x;

  // Member: gyr_y
  cdr >> ros_message.gyr_y;

  // Member: gyr_z
  cdr >> ros_message.gyr_z;

  // Member: temp
  cdr >> ros_message.temp;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_more_interfaces
get_serialized_size(
  const more_interfaces::msg::Readings & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: acc_x
  {
    size_t item_size = sizeof(ros_message.acc_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: acc_y
  {
    size_t item_size = sizeof(ros_message.acc_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: acc_z
  {
    size_t item_size = sizeof(ros_message.acc_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyr_x
  {
    size_t item_size = sizeof(ros_message.gyr_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyr_y
  {
    size_t item_size = sizeof(ros_message.gyr_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: gyr_z
  {
    size_t item_size = sizeof(ros_message.gyr_z);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: temp
  {
    size_t item_size = sizeof(ros_message.temp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_more_interfaces
max_serialized_size_Readings(
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


  // Member: acc_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: acc_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: acc_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyr_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyr_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: gyr_z
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: temp
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = more_interfaces::msg::Readings;
    is_plain =
      (
      offsetof(DataType, temp) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _Readings__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const more_interfaces::msg::Readings *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Readings__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<more_interfaces::msg::Readings *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Readings__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const more_interfaces::msg::Readings *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Readings__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_Readings(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _Readings__callbacks = {
  "more_interfaces::msg",
  "Readings",
  _Readings__cdr_serialize,
  _Readings__cdr_deserialize,
  _Readings__get_serialized_size,
  _Readings__max_serialized_size
};

static rosidl_message_type_support_t _Readings__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Readings__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace more_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_more_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<more_interfaces::msg::Readings>()
{
  return &more_interfaces::msg::typesupport_fastrtps_cpp::_Readings__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, more_interfaces, msg, Readings)() {
  return &more_interfaces::msg::typesupport_fastrtps_cpp::_Readings__handle;
}

#ifdef __cplusplus
}
#endif
