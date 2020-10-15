 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)
include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/phys/physlist/include)
include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/electrostatics/kernals/include)

#
#      Define the OpenTuCo Module: Electrostatics
#

project(electricparticles)

include_directories(include)
set(SOURCE_LIB include/electricparticle.h src/electricparticle.cpp
               include/charge.h src/charge.cpp
               include/dipole.h src/dipole.cpp
               include/quadrupole.h src/quadrupole.cpp)
add_library(electricparticles STATIC ${SOURCE_LIB})

