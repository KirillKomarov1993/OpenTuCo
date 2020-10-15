 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

# include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module
#

project(statphys)

include_directories(include)
set(SOURCE_LIB include/materialpoint.h src/materialpoint.cpp
               include/physstate.h src/physstate.cpp
               include/ensemble.h src/ensemble.cpp)
add_library(statphys STATIC ${SOURCE_LIB})

