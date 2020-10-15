 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR})

#
# Define the OpenTuCo Module
#

project(algebra)

include_directories(include)
set(SOURCE_LIB include/scalar.h src/scalar.cpp
               include/strength.h src/strength.cpp
               include/functional.h src/functional.cpp)
add_library(algebra STATIC ${SOURCE_LIB})

