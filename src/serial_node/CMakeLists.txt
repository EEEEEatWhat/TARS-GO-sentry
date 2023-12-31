cmake_minimum_required(VERSION 3.8)
project(serial_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(serial_node src/serial_node.cpp)
ament_target_dependencies(
  serial_node
  "rclcpp"
  "std_msgs"
)
add_executable(serial_node3 src/serial_node3.cpp)
ament_target_dependencies(
  serial_node3
  "rclcpp"
  "std_msgs"
  sensor_msgs
)
add_executable(serial_node2 src/serial_node2.cpp)
ament_target_dependencies(
  serial_node2
  "rclcpp"
  "std_msgs"
)
add_executable(CH34x_serial src/CH34x_seiral.cpp)
ament_target_dependencies(
  CH34x_serial
  "rclcpp"
  "std_msgs"
  geometry_msgs
)
install(TARGETS 
  serial_node
  serial_node2
  serial_node3
  CH34x_serial
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch config
DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
