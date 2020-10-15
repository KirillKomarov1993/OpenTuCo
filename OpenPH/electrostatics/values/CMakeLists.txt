 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#
#      Define the OpenTuCo Module: Values
#

project(values)

include_directories(include)
set(SOURCE_LIB include/potential.h src/potential.cpp
               include/electricstrength.h src/electricstrength.cpp)
add_library(values STATIC ${SOURCE_LIB})

