 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/OpenPH/phys/physlist/include)

#
# Define the OpenCS Module: Structure
#

project(structures)

include_directories(include)
set(SOURCE_LIB include/basis.h src/basis.cpp
               include/reciprocallattice.h src/reciprocallattice.cpp
               include/bravaislattice.h src/bravaislattice.cpp
               include/particle.h src/particle.cpp
               include/lattice.h src/lattice.cpp
               include/structure.h src/structure.cpp
               include/structurebuilder.h src/structurebuilder.cpp)

add_library(structures STATIC ${SOURCE_LIB})

