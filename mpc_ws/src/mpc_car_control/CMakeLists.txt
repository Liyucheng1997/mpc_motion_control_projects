cmake_minimum_required(VERSION 3.5)
project(mpc_car_control)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/VehicleState.msg"
  "msg/ReferenceTrajectory.msg"
  "msg/ControlCommandBody.msg"
  "msg/ActuatorCommand.msg"
  "msg/WheelGroundHeights.msg"
  DEPENDENCIES geometry_msgs std_msgs
)

add_executable(scenario_generator_node src/scenario_generator_node.cpp)
ament_target_dependencies(scenario_generator_node rclcpp std_msgs geometry_msgs visualization_msgs tf2 tf2_ros)
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
target_link_libraries(scenario_generator_node "${cpp_typesupport_target}")

install(TARGETS
  scenario_generator_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(mpc_controller_node src/mpc_controller_node.cpp)
ament_target_dependencies(mpc_controller_node rclcpp std_msgs geometry_msgs)
target_link_libraries(mpc_controller_node "${cpp_typesupport_target}")

install(TARGETS
  mpc_controller_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(control_allocator_node src/control_allocator_node.cpp)
ament_target_dependencies(control_allocator_node rclcpp std_msgs geometry_msgs)
target_link_libraries(control_allocator_node "${cpp_typesupport_target}")

add_executable(pid_controller_node src/pid_controller_node.cpp)
ament_target_dependencies(pid_controller_node rclcpp std_msgs geometry_msgs)
target_link_libraries(pid_controller_node "${cpp_typesupport_target}")

add_executable(vehicle_interface_node src/vehicle_interface_node.cpp)
ament_target_dependencies(vehicle_interface_node rclcpp std_msgs geometry_msgs)
target_link_libraries(vehicle_interface_node "${cpp_typesupport_target}")

add_executable(visualization_node src/visualization_node.cpp)
ament_target_dependencies(visualization_node
  rclcpp
  std_msgs
  visualization_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
)
target_link_libraries(visualization_node "${cpp_typesupport_target}")

add_executable(vehicle_model_node src/vehicle_model_node.cpp)
ament_target_dependencies(vehicle_model_node rclcpp std_msgs)
target_link_libraries(vehicle_model_node "${cpp_typesupport_target}")

install(TARGETS
  control_allocator_node
  pid_controller_node
  vehicle_interface_node
  visualization_node
  vehicle_model_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(PROGRAMS
  viz/az_plotter.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
