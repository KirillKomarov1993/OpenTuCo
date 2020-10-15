 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/mesh/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/space/include)
#
# Define the OpenTuCo Module
#

project(shapes)

include_directories(include)
set(SOURCE_LIB include/shape.h src/shape.cpp
               include/box.h src/box.cpp
               include/dick.h src/dick.cpp
               include/sphere.h src/sphere.cpp
               include/ellipsoid.h src/ellipsoid.cpp)
add_library(shapes STATIC ${SOURCE_LIB})

