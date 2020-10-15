cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles/include)
#add_subdirectory(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles)

#
# Define the OpenTuCo Module: Method/EEM
#

project(eem)

include_directories(include)
set(SOURCE_LIB include/energyelementmethod.h src/energyelementmethod.cpp
	       include/clusterenergymethod.h src/clusterenergymethod.cpp)
               #include/crystalelementmethod.h src/crystalelementmethod.cpp
               
add_library(eem STATIC ${SOURCE_LIB})

