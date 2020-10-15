 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/math/include)

#
#      Define the OpenTuCo Module: Geometry/Space
#

project(space)

include_directories(include)
set(SOURCE_LIB include/space.h src/space.cpp
               include/point.h src/point.cpp
               include/pointlist.h src/pointlist.cpp)
add_library(space STATIC ${SOURCE_LIB})

