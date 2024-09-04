cmake_minimum_required(VERSION 3.8)
project(c_msg_coms)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interface REQUIRED) 

add_executable(talker src/publisher.cpp)
ament_target_dependencies(talker rclcpp my_interface)

add_executable(listener src/suscriber.cpp)
ament_target_dependencies(listener rclcpp my_interface)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()
