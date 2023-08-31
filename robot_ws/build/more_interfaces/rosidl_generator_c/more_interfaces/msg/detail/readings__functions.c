// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from more_interfaces:msg/Readings.idl
// generated code does not contain a copyright notice
#include "more_interfaces/msg/detail/readings__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
more_interfaces__msg__Readings__init(more_interfaces__msg__Readings * msg)
{
  if (!msg) {
    return false;
  }
  // acc_x
  // acc_y
  // acc_z
  // gyr_x
  // gyr_y
  // gyr_z
  return true;
}

void
more_interfaces__msg__Readings__fini(more_interfaces__msg__Readings * msg)
{
  if (!msg) {
    return;
  }
  // acc_x
  // acc_y
  // acc_z
  // gyr_x
  // gyr_y
  // gyr_z
}

bool
more_interfaces__msg__Readings__are_equal(const more_interfaces__msg__Readings * lhs, const more_interfaces__msg__Readings * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // acc_x
  if (lhs->acc_x != rhs->acc_x) {
    return false;
  }
  // acc_y
  if (lhs->acc_y != rhs->acc_y) {
    return false;
  }
  // acc_z
  if (lhs->acc_z != rhs->acc_z) {
    return false;
  }
  // gyr_x
  if (lhs->gyr_x != rhs->gyr_x) {
    return false;
  }
  // gyr_y
  if (lhs->gyr_y != rhs->gyr_y) {
    return false;
  }
  // gyr_z
  if (lhs->gyr_z != rhs->gyr_z) {
    return false;
  }
  return true;
}

bool
more_interfaces__msg__Readings__copy(
  const more_interfaces__msg__Readings * input,
  more_interfaces__msg__Readings * output)
{
  if (!input || !output) {
    return false;
  }
  // acc_x
  output->acc_x = input->acc_x;
  // acc_y
  output->acc_y = input->acc_y;
  // acc_z
  output->acc_z = input->acc_z;
  // gyr_x
  output->gyr_x = input->gyr_x;
  // gyr_y
  output->gyr_y = input->gyr_y;
  // gyr_z
  output->gyr_z = input->gyr_z;
  return true;
}

more_interfaces__msg__Readings *
more_interfaces__msg__Readings__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  more_interfaces__msg__Readings * msg = (more_interfaces__msg__Readings *)allocator.allocate(sizeof(more_interfaces__msg__Readings), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(more_interfaces__msg__Readings));
  bool success = more_interfaces__msg__Readings__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
more_interfaces__msg__Readings__destroy(more_interfaces__msg__Readings * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    more_interfaces__msg__Readings__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
more_interfaces__msg__Readings__Sequence__init(more_interfaces__msg__Readings__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  more_interfaces__msg__Readings * data = NULL;

  if (size) {
    data = (more_interfaces__msg__Readings *)allocator.zero_allocate(size, sizeof(more_interfaces__msg__Readings), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = more_interfaces__msg__Readings__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        more_interfaces__msg__Readings__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
more_interfaces__msg__Readings__Sequence__fini(more_interfaces__msg__Readings__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      more_interfaces__msg__Readings__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

more_interfaces__msg__Readings__Sequence *
more_interfaces__msg__Readings__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  more_interfaces__msg__Readings__Sequence * array = (more_interfaces__msg__Readings__Sequence *)allocator.allocate(sizeof(more_interfaces__msg__Readings__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = more_interfaces__msg__Readings__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
more_interfaces__msg__Readings__Sequence__destroy(more_interfaces__msg__Readings__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    more_interfaces__msg__Readings__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
more_interfaces__msg__Readings__Sequence__are_equal(const more_interfaces__msg__Readings__Sequence * lhs, const more_interfaces__msg__Readings__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!more_interfaces__msg__Readings__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
more_interfaces__msg__Readings__Sequence__copy(
  const more_interfaces__msg__Readings__Sequence * input,
  more_interfaces__msg__Readings__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(more_interfaces__msg__Readings);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    more_interfaces__msg__Readings * data =
      (more_interfaces__msg__Readings *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!more_interfaces__msg__Readings__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          more_interfaces__msg__Readings__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!more_interfaces__msg__Readings__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
