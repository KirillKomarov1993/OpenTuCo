 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/phys/physlist/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module: Integral Equation
#

project(integralequation)

include_directories(include)
set(SOURCE_LIB include/kernalset.h src/kernalset.cpp
               include/integralequation.h src/integralequation.cpp
               include/surfacepolarizationequation.h src/surfacepolarizationequation.cpp
               include/pseudosurfacepolarizationmethod.h src/pseudosurfacepolarizationmethod.cpp
               include/surfaceenergyequation.h src/surfaceenergyequation.cpp
               include/conductorscreeningmodel.h src/conductorscreeningmodel.cpp)
add_library(integralequation STATIC ${SOURCE_LIB})

