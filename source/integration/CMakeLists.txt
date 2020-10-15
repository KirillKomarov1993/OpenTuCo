 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/phys/physlist/include)
#include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module: Integration
#

project(integration)

include_directories(include)
set(SOURCE_LIB include/integration.h src/integration.cpp
               include/montecarlointegration.h src/montecarlointegration.cpp
               include/symplexintegration.h src/symplexintegration.cpp)
add_library(integration STATIC ${SOURCE_LIB})

