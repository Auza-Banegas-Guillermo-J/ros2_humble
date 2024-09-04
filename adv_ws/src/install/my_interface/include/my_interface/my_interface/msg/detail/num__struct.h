// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interface:msg/Num.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__MSG__DETAIL__NUM__STRUCT_H_
#define MY_INTERFACE__MSG__DETAIL__NUM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Num in the package my_interface.
typedef struct my_interface__msg__Num
{
  int64_t num;
} my_interface__msg__Num;

// Struct for a sequence of my_interface__msg__Num.
typedef struct my_interface__msg__Num__Sequence
{
  my_interface__msg__Num * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interface__msg__Num__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACE__MSG__DETAIL__NUM__STRUCT_H_
