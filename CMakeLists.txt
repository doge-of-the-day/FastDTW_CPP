cmake_minimum_required(VERSION 2.8.3)
project(fastdtw_cpp)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
set(FAST_DTW_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE ${FAST_DTW_FLAGS})

find_package(OpenCV QUIET)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES fastdtw_cpp
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
    include/fastdtw_cpp/mask.hpp
    include/fastdtw_cpp/downsampling.hpp
    src/fastdtw_cpp.cpp
)

if(${OpenCV_FOUND})
add_executable(fastdtw_path_visual
    src/path_visual.cpp
)
target_link_libraries(fastdtw_path_visual
    ${OpenCV_LIBRARIES}
)

find_package(CUDA QUIET)
if(${CUDA_FOUND})
message("FASTDTW CUDA EXTENSION WILL BE BUILT")
endif()
endif()
