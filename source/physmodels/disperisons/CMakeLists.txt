 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#include_directories(${CMAKE_SOURCE_DIR}/source/math/include)


# Define the OpenTuCo Module: Models/Disperisons

project(disperisons)

include_directories(include)
set(SOURCE_LIB include/dispersionmodel.h src/dispersionmodel.cpp)
add_library(disperisons STATIC ${SOURCE_LIB})

