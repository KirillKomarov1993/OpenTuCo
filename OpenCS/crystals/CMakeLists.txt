 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR})

#
# Define the OpenCS Module: Crystal
#

project(crystals)

include_directories(include)
set(SOURCE_LIB include/crystalmanager.h src/crystalmanager.cpp
               include/unitcell.h src/unitcell.cpp
               include/virtualshift.h src/virtualshift.cpp
               include/node.h src/node.cpp
               include/virtualnode.h src/virtualnode.cpp
	       include/crystalbuilder.h src/crystalbuilder.cpp
               include/realcrystalbuilder.h src/realcrystalbuilder.cpp
               include/virtualcrystalbuilder.h src/virtualcrystalbuilder.cpp
               include/crystal.h src/crystal.cpp
               include/realcrystal.h src/realcrystal.cpp
               include/virtualcrystal.h src/virtualcrystal.cpp
               include/elasticproperties.h src/elasticproperties.cpp)
add_library(crystals STATIC ${SOURCE_LIB})
