// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from more_interfaces:msg/Controls.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__CONTROLS__TRAITS_HPP_
#define MORE_INTERFACES__MSG__DETAIL__CONTROLS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "more_interfaces/msg/detail/controls__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace more_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Controls & msg,
  std::ostream & out)
{
  out << "{";
  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << ", ";
  }

  // member: steering
  {
    out << "steering: ";
    rosidl_generator_traits::value_to_yaml(msg.steering, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Controls & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }

  // member: steering
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering: ";
    rosidl_generator_traits::value_to_yaml(msg.steering, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Controls & msg, bool use_flow_style = false)
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
  const more_interfaces::msg::Controls & msg,
  std::ostream & out, size_t indentation = 0)
{
  more_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use more_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const more_interfaces::msg::Controls & msg)
{
  return more_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<more_interfaces::msg::Controls>()
{
  return "more_interfaces::msg::Controls";
}

template<>
inline const char * name<more_interfaces::msg::Controls>()
{
  return "more_interfaces/msg/Controls";
}

template<>
struct has_fixed_size<more_interfaces::msg::Controls>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<more_interfaces::msg::Controls>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<more_interfaces::msg::Controls>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MORE_INTERFACES__MSG__DETAIL__CONTROLS__TRAITS_HPP_
