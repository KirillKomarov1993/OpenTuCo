 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

# include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module
#

project(atomcrystal)

include_directories(include)
set(SOURCE_LIB include/atompotential.h src/atompotential.cpp
               include/atom.h src/atom.cpp
               include/atomcrystal.h src/atomcrystal.cpp)
add_library(atomcrystal STATIC ${SOURCE_LIB})

