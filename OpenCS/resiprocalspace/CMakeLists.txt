 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/OpenPH/phys/physlist/include)

#
# Define the OpenCS Module: Resiprocal Space
#

project(resiprocalspace)

include_directories(include)
set(SOURCE_LIB include/wavevector.h src/wavevector.cpp
               include/direction.h src/direction.cpp
	       include/brillouinzone.h src/brillouinzone.cpp)

add_library(resiprocalspace STATIC ${SOURCE_LIB})

