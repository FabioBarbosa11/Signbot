cmake_minimum_required(VERSION 2.8.3)
project(signbot_plugins)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  trajectory_msgs

  geometry_msgs
  mongodb_store
  std_msgs
  std_srvs)

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   gestureInformation.msg
 )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
INCLUDE_DIRS include
LIBRARIES signbot_plugins
CATKIN_DEPENDS
      message_runtime
      roscpp
      trajectory_msgs

      geometry_msgs mongodb_store std_msgs std_srvs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
 add_library(classtranslator src/classtranslator.cpp)
 add_library(signbotcontroll src/signbot_controll.cpp)
 add_library(signbotdb src/signbotdb.cpp)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
  add_dependencies(classtranslator ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
  add_dependencies(signbotcontroll ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
  add_dependencies(signbotdb ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

  target_link_libraries(signbotdb ${catkin_LIBRARIES})
  target_link_libraries(signbotcontroll ${catkin_LIBRARIES})
  target_link_libraries(classtranslator signbotcontroll signbotdb ${catkin_LIBRARIES})




  add_executable(example_1pose_node src/example_1pose.cpp)
  add_dependencies(example_1pose_node example_1pose_cpp)
  target_link_libraries(example_1pose_node ${catkin_LIBRARIES})

  add_executable(example_signbot_core_node src/example_signbot_core.cpp)
  add_dependencies(example_signbot_core_node example_signbot_core_cpp)
  target_link_libraries(example_signbot_core_node ${catkin_LIBRARIES})

  add_executable(example_bom_dia_node src/example_bom_dia.cpp)
  add_dependencies(example_bom_dia_node example_bom_dia_cpp)
  target_link_libraries(example_bom_dia_node ${catkin_LIBRARIES})

  add_executable(example_signbot_db_core_node src/example_signbot_db_core.cpp)
  add_dependencies(example_signbot_db_core_node example_signbot_db_core_cpp)
  target_link_libraries(example_signbot_db_core_node ${catkin_LIBRARIES})

  add_executable(example_multiarray_msg_node src/example_multiarray_msg.cpp)
  add_dependencies(example_multiarray_msg_node example_multiarray_msg_cpp)
  target_link_libraries(example_multiarray_msg_node ${catkin_LIBRARIES})

  add_executable(example_other_multiarray_msg_node src/example_other_multiarray_msg.cpp)
  add_dependencies(example_other_multiarray_msg_node example_other_multiarray_msg_cpp)
  target_link_libraries(example_other_multiarray_msg_node ${catkin_LIBRARIES})

  add_executable(signbot_core_node src/signbot_core.cpp)
  add_dependencies(signbot_core_node signbot_core_cpp)
  target_link_libraries(signbot_core_node classtranslator signbotcontroll signbotdb ${catkin_LIBRARIES})
