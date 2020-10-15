 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

# include_directories(${CMAKE_SOURCE_DIR}/source/OpenPH/math/mathlist/include)

#
# Define the OpenTuCo Module
#

project(processing)

include_directories(include)
set(SOURCE_LIB include/processing.h src/processing.cpp
               include/wienermethod.h src/wienermethod.cpp
               include/hartmanmethod.h src/hartmanmethod.cpp
               include/dynamicstructurefactor.h src/dynamicstructurefactor.cpp)
add_library(processing STATIC ${SOURCE_LIB})

