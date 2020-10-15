 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR})

#
# Define the OpenCS Module: Optimizer
#

project(optimizer)

include_directories(include)
set(SOURCE_LIB include/optimizationalgorithm.h src/optimizationalgorithm.cpp
               include/methodgradientdescent.h src/methodgradientdescent.cpp
               include/externaloptimizer.h src/externaloptimizer.cpp)
add_library(optimizer STATIC ${SOURCE_LIB})
