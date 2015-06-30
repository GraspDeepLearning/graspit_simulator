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
  INCLUDE_DIRS . $ENV{GRASPIT} $ENV{GRASPIT}/include $ENV{GRASPIT}/src/Collision $ENV{GRASPIT}/src/DBase $ENV{GRASPIT}/src/DBase/DBPlanner
#  LIBRARIES test
  CATKIN_DEPENDS ${PACKAGE_DEPS}
#  DEPENDS system_lib
)

include_directories(
        ${catkin_INCLUDE_DIRS}
        )
add_custom_target(graspit_build ALL
  DEPENDS $ENV{GRASPIT}/graspit.pro 
  COMMAND cd $ENV{GRASPIT} && qmake graspit.pro && make
  COMMAND cp $ENV{GRASPIT}/bin/graspit ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/graspit
)




add_dependencies(graspit_build household_objects_database)
install(DIRECTORY $ENV{GRASPIT}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)

#install(PROGRAMS
#   $ENV{GRASPIT}/bin/graspit
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

