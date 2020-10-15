 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/math/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/space/include)

#
# Define the OpenTuCo Module
#

project(mesh)

include_directories(include)
set(SOURCE_LIB include/polygon.h src/polygon.cpp
               include/mesh.h src/mesh.cpp)
add_library(mesh STATIC ${SOURCE_LIB})

