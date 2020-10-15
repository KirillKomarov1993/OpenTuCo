 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR})

#
# Define the OpenTuCo Module
#

project(mathlsit)

include_directories(include)
set(SOURCE_LIB include/mathlist.h src/mathlist.cpp)
add_library(mathlist STATIC ${SOURCE_LIB})

