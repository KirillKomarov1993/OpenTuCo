 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/physlist/algebra/include)
include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/phys/physlist/include)
include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/electrostatics/kernals/include)

#
#      Define the OpenTuCo Module: ElectricFields
#

project(electricfields)

include_directories(include)
set(SOURCE_LIB include/homogemiusfield.h src/homogemiusfield.cpp
               include/rotatingelectricfield.h src/rotatingelectricfield.cpp
               include/electricfield.h src/electricfield.cpp)
add_library(electricfields STATIC ${SOURCE_LIB})

