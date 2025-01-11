cmake_minimum_required(VERSION 3.8)
project(my_cashier_system)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(std_srvs REQUIRED)
find_package(tutorial_interfaces REQUIRED)
include_directories(include)
# Add the Bill Publisher node
add_executable(bill_publisher src/bill_publish_node.cpp)
ament_target_dependencies(bill_publisher rclcpp tutorial_interfaces)

# Add the Manager node
add_executable(manager_node src/bill_subscriber_node.cpp)
ament_target_dependencies(manager_node rclcpp tutorial_interfaces std_srvs)

# Add the Monitor node
add_executable(monitor_node src/bill_display_node.cpp)
ament_target_dependencies(monitor_node rclcpp tutorial_interfaces)



# Install executables
install(TARGETS
  bill_publisher
  manager_node
  monitor_node
  
  DESTINATION lib/${PROJECT_NAME}
)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

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