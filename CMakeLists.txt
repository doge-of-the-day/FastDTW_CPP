cmake_minimum_required(VERSION 2.8.3)
project(fastdtw_cpp)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall -O3 -march=core2 -Os")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no
C++11 support. Please use a different C++ compiler.")
endif()

find_package(OpenCV QUIET)
find_package(Boost  QUIET)

catkin_package(
  INCLUDE_DIRS  include
  LIBRARIES     fastdtw_cpp
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(fastdtw_cpp
    include/fastdtw_cpp/distances.h
    include/fastdtw_cpp/dtw.h
    include/fastdtw_cpp/fastdtw.h
    include/fastdtw_cpp/path.h
    include/fastdtw_cpp/projection.h
    include/fastdtw_cpp/projection_idc.h
    include/fastdtw_cpp/utils.h
    include/fastdtw_cpp/mask.h
    include/fastdtw_cpp/downsampling.h

    src/distances.cpp
    src/dtw.cpp
    src/fastdtw.cpp
    src/path.cpp
    src/projection.cpp
    src/projection_idc.cpp
    src/utils.cpp
    src/mask.cpp
    src/downsampling.cpp

)

add_executable(fastdtw_cpp_test
    src/fastdtw_cpp.cpp
)
target_link_libraries(fastdtw_cpp_test
    fastdtw_cpp
)


if(${OpenCV_FOUND} AND ${Boost_FOUND})
add_executable(fastdtw_path_visual
    src/path_visual.cpp
)
target_link_libraries(fastdtw_path_visual
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
    fastdtw_cpp
)
endif()
