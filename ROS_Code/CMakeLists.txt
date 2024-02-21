cmake_minimum_required(VERSION 3.0.2)
project(pvdf)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  serial
  std_msgs
  geometry_msgs
)

add_message_files(
  FILES
  pvdf_msg.msg
)

generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs  # Or other packages containing msgs
)

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES pvdf
  CATKIN_DEPENDS message_generation roscpp serial message_runtime rospy
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pvdf_scan src/pvdf_scan.cpp)
target_link_libraries(pvdf_scan
  ${catkin_LIBRARIES}
)
