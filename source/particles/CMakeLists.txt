 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/math/include)
include_directories(${CMAKE_SOURCE_DIR}/source/phys/include)
include_directories(${CMAKE_SOURCE_DIR}/source/materials/include)
include_directories(${CMAKE_SOURCE_DIR}/source/electrostatics/electricparticles/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/shapes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/interactions/include)


#
#      Define the OpenTuCo Module: Particles
#

project(colloids)

include_directories(include)
set(SOURCE_LIB include/particlebuilder.h src/particlebuilder.cpp
               include/corelinker.h src/corelinker.cpp
               include/macroparticle.h src/macroparticle.cpp
               include/colloid.h src/colloid.cpp
               include/cscolloid.h src/cscolloid.cpp
               include/state.h src/state.cpp
               include/physicalmesh.h src/physicalmesh.cpp
               include/electricmesh.h src/electricmesh.cpp)
add_library(colloids STATIC ${SOURCE_LIB})

