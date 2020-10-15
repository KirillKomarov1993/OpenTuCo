 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

# include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module
#

project(phonon)

include_directories(include)
set(SOURCE_LIB include/phonon.h src/phonon.cpp 
               include/phononspectrum.h src/phononspectrum.cpp)
add_library(phonon STATIC ${SOURCE_LIB})

