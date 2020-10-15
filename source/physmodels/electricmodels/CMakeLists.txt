 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/math/include)


# Define the OpenTuCo Module: Models/Electric

project(electricmodels)

include_directories(include)
set(SOURCE_LIB include/physicalmodel.h src/physicalmodel.cpp
               include/dipolemodel.h src/dipolemodel.cpp
               include/hardobjectmodel.h src/hardobjectmodel.cpp
               include/colloidmodel.h src/colloidmodel.cpp)
add_library(electricmodels STATIC ${SOURCE_LIB})

