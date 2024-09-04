# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_c_msg_coms_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED c_msg_coms_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(c_msg_coms_FOUND FALSE)
  elseif(NOT c_msg_coms_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(c_msg_coms_FOUND FALSE)
  endif()
  return()
endif()
set(_c_msg_coms_CONFIG_INCLUDED TRUE)

# output package information
if(NOT c_msg_coms_FIND_QUIETLY)
  message(STATUS "Found c_msg_coms: 0.0.0 (${c_msg_coms_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'c_msg_coms' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${c_msg_coms_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(c_msg_coms_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${c_msg_coms_DIR}/${_extra}")
endforeach()
