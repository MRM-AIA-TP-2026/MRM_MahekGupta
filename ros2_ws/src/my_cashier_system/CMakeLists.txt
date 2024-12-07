cmake_minimum_required(VERSION 3.8)
project(my_cashier_system)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tutorial_interfaces REQUIRED)
# Add your executables
#add_executable(bill src/bill_publish_node.cpp)
#add_executable(bill_subscriber_node src/bill_subscriber_node.cpp)

# Link the executables to the necessary dependencies
#ament_target_dependencies(bill rclcpp tutorial_interfaces)
#ament_target_dependencies(bill_subscriber_node rclcpp tutorial_interfaces)

# Install your executables
#install(TARGETS
  #bill
  #bill_subscriber_node
  #bill_display_node
  #DESTINATION lib/${PROJECT_NAME}
#)
add_executable(bill_publisher_node src/bill_publish_node.cpp)
ament_target_dependencies(bill_publisher_node rclcpp tutorial_interfaces)

add_executable(bill_subscriber_node src/bill_subscriber_node.cpp)
ament_target_dependencies(bill_subscriber_node rclcpp tutorial_interfaces)
add_executable(bill_display_node src/bill_display_node.cpp)
ament_target_dependencies(bill_display_node rclcpp tutorial_interfaces)


install(TARGETS
 bill_publisher_node
 bill_subscriber_node
 bill_display_node
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()