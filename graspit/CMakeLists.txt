cmake_minimum_required(VERSION 2.8.3)
project(graspit)

set(PACKAGE_DEPS
  household_objects_database
)

find_package(catkin REQUIRED COMPONENTS ${PACKAGE_DEPS})


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
  INCLUDE_DIRS . graspit_source graspit_source/include graspit_source/src/Collision graspit_source/src/DBase graspit_source/src/DBase/DBPlanner
#  LIBRARIES test
  CATKIN_DEPENDS ${PACKAGE_DEPS}
#  DEPENDS system_lib
)

include_directories(
        ${catkin_INCLUDE_DIRS}
        )


add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/ros-interactive-manipulation/graspit_simulator/${PROJECT_NAME}/graspit_source/graspit.pro
  COMMAND svn co svn://svn.code.sf.net/p/graspit/code/trunk -rHEAD graspit_source
  COMMAND patch -N -d graspit_source -p0 < graspit_project.patch
  COMMAND patch -N -d graspit_source -p0 < graspit_dbase.patch
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}
)

add_custom_target(graspit_build ALL
  DEPENDS ${CMAKE_SOURCE_DIR}/ros-interactive-manipulation/graspit_simulator/${PROJECT_NAME}/graspit_source/graspit.pro
  COMMAND qmake "EXT_DESTDIR = ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}" ${CMAKE_SOURCE_DIR}/ros-interactive-manipulation/graspit_simulator/${PROJECT_NAME}/graspit_source/graspit.pro
  COMMAND make
)

add_dependencies(graspit_build household_objects_database)

install(DIRECTORY graspit_source/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
