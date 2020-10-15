cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles/include)
#add_subdirectory(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles)

#
# Define the OpenTuCo Module: Method/TuCo
#

project(tucomethods)

include_directories(include)
set(SOURCE_LIB include/tucomethod.h src/tucomethod.cpp)
add_library(tucomethods STATIC ${SOURCE_LIB})

