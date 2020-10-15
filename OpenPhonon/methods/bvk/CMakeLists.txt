 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

# include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module
#

project(bvk)

include_directories(include)
set(SOURCE_LIB include/bornvonkarman.h src/bornvonkarman.cpp 
               include/dynamicsmatrix.h src/dynamicsmatrix.cpp
	       include/element.h src/element.cpp
	       include/forceblocks.h src/forceblocks.cpp
               include/forcematrix.h src/forcematrix.cpp)
add_library(bvk STATIC ${SOURCE_LIB})

