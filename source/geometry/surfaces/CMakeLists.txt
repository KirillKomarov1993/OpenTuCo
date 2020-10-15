 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/OpenPN/math/mathlist/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/mesh/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/space/include)
#
# Define the OpenTuCo Module
#

project(surfaces)

include_directories(include)
set(SOURCE_LIB include/surface.h src/surface.cpp
               include/plane.h src/plane.cpp)
add_library(surfaces STATIC ${SOURCE_LIB})

