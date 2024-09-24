cmake_minimum_required(VERSION 3.8)
project(c_moveit)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(geometric_shapes REQUIRED)
find_package(shape_msgs REQUIRED)

add_executable(hello_moveit src/hello_moveit.cpp)
ament_target_dependencies(hello_moveit rclcpp moveit_ros_planning_interface geometric_shapes shape_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
hello_moveit
DESTINATION lib/${PROJECT_NAME})

ament_package()
