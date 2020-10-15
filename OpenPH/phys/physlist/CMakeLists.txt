 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module
#

project(physlist)

include_directories(include)
set(SOURCE_LIB src/physlist.cpp include/physlist.h
               src/energy.cpp include/energy.h
               include/potentialenergy.h src/potentialenergy.cpp)
add_library(physlist STATIC ${SOURCE_LIB})

