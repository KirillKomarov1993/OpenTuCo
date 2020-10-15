cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles/include)
#add_subdirectory(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles)

#
# Define the OpenTuCo Module: Method/BEM
#

project(bem)

include_directories(include)
set(SOURCE_LIB include/boundaryelementmethod.h src/boundaryelementmethod.cpp
               include/crystalelementmethod.h src/crystalelementmethod.cpp
               include/clusterelementmethod.h src/clusterelementmethod.cpp)
               #include/integralequation.h src/integralequation.cpp
               #include/surfacepolarizationequation.h src/surfacepolarizationequation.cpp
               #include/pseudosurfacepolarizationmethod.h src/pseudosurfacepolarizationmethod.cpp)
add_library(bem STATIC ${SOURCE_LIB})

