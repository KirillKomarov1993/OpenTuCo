 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/phys/physlist/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module: BoundaryElements
#

project(boundaryelements)

include_directories(include)
set(SOURCE_LIB include/boundaryelement.h src/boundaryelement.cpp
               include/electricelement.h src/electricelement.cpp)
add_library(boundaryelements STATIC ${SOURCE_LIB})

