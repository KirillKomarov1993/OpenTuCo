 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/math/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/phys/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/materials/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/electrostatics/electricparticles/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/geometry/shapes/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/interactions/include)

# Define the OpenTuCo Module: Systems

project(systems)

include_directories(include)
set(SOURCE_LIB include/tunablesystem.h src/tunablesystem.cpp
               include/tunablecrystal.h src/tunablecrystal.cpp
               include/tunablecluster.h src/tunablecluster.cpp
               include/medium.h src/medium.cpp
               include/crystalfunctional.h src/crystalfunctional.cpp
               include/crystaldeformationmethod.h src/crystaldeformationmethod.cpp)
               #include/cluster.h src/cluster.cpp
               #include/stabilization.h src/stabilization.cpp)
add_library(systems STATIC ${SOURCE_LIB})

