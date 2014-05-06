cmake_minimum_required(VERSION 2.8.3)
project(fastdtw_cpp)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES fastdtw_cpp
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

#### TODO : REMOVE BUILD ####

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

## Declare a cpp library
add_executable(fastdtw_cpp
    include/fastdtw_cpp/dtw.hpp
    include/fastdtw_cpp/distances.hpp
    include/fastdtw_cpp/fastdtw.hpp
    include/fastdtw_cpp/path.hpp
    include/fastdtw_cpp/projection.hpp
    include/fastdtw_cpp/utils.hpp

    src/fastdtw_cpp.cpp
)

add_executable(projection
    src/opencv.cpp
)

target_link_libraries(projection
    ${OpenCV_LIBRARIES}
)
