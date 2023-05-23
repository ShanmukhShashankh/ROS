cmake_minimum_required(VERSION 3.8)
project(r2d2_controller_cpp)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(cpp_node src/first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)

add_executable(draw_circle src/draw_circle.cpp)
ament_target_dependencies(draw_circle rclcpp geometry_msgs)

add_executable(pose_subsciber src/pose_subscriber.cpp)
ament_target_dependencies(pose_subsciber rclcpp turtlesim)

add_executable(turtle_controller src/turtle_controller.cpp)
ament_target_dependencies(turtle_controller rclcpp turtlesim geometry_msgs)

add_executable(number_counter src/number_counter.cpp)
ament_target_dependencies(number_counter rclcpp example_interfaces)

add_executable(number_publisher src/number_publisher.cpp)
ament_target_dependencies(number_publisher rclcpp example_interfaces)

install(TARGETS
  cpp_node
  draw_circle
  pose_subsciber
  turtle_controller
  number_counter
  number_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
