 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/math/include)


#
#      Define the OpenTuCo Module: Hamiltanian
#

project(hamiltanian)

include_directories(include)
set(SOURCE_LIB include/hamiltanian.h src/hamiltanian.cpp
               include/keezomenergy.h src/keezomenergy.cpp
               include/madelungenergy.h src/madelungenergy.cpp)
add_library(hamiltanian STATIC ${SOURCE_LIB})

