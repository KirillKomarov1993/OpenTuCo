 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)
include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/phys/physlist/include)


# Define the OpenTuCo Module: Electrostatics/greenkernal

project(kernals)

include_directories(include)
set(SOURCE_LIB src/greenkernal.cpp include/greenkernal.h
               src/coulombkernal.cpp include/coulombkernal.h
               src/yukawakernal.cpp include/yukawakernal.h )
add_library(kernals STATIC ${SOURCE_LIB})

