// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from more_interfaces:msg/Readings.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__READINGS__TRAITS_HPP_
#define MORE_INTERFACES__MSG__DETAIL__READINGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "more_interfaces/msg/detail/readings__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace more_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Readings & msg,
  std::ostream & out)
{
  out << "{";
  // member: acc_x
  {
    out << "acc_x: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_x, out);
    out << ", ";
  }

  // member: acc_y
  {
    out << "acc_y: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_y, out);
    out << ", ";
  }

  // member: acc_z
  {
    out << "acc_z: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_z, out);
    out << ", ";
  }

  // member: gyr_x
  {
    out << "gyr_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyr_x, out);
    out << ", ";
  }

  // member: gyr_y
  {
    out << "gyr_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyr_y, out);
    out << ", ";
  }

  // member: gyr_z
  {
    out << "gyr_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyr_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Readings & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: acc_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_x: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_x, out);
    out << "\n";
  }

  // member: acc_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_y: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_y, out);
    out << "\n";
  }

  // member: acc_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_z: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_z, out);
    out << "\n";
  }

  // member: gyr_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyr_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyr_x, out);
    out << "\n";
  }

  // member: gyr_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyr_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyr_y, out);
    out << "\n";
  }

  // member: gyr_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyr_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyr_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Readings & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace more_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use more_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const more_interfaces::msg::Readings & msg,
  std::ostream & out, size_t indentation = 0)
{
  more_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use more_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const more_interfaces::msg::Readings & msg)
{
  return more_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<more_interfaces::msg::Readings>()
{
  return "more_interfaces::msg::Readings";
}

template<>
inline const char * name<more_interfaces::msg::Readings>()
{
  return "more_interfaces/msg/Readings";
}

template<>
struct has_fixed_size<more_interfaces::msg::Readings>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<more_interfaces::msg::Readings>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<more_interfaces::msg::Readings>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MORE_INTERFACES__MSG__DETAIL__READINGS__TRAITS_HPP_
