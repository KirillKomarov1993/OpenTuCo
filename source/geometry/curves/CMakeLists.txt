 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

project(curves)

include_directories(include)
set(SOURCE_LIB include/curve.h src/curve.cpp)

add_library(curves STATIC ${SOURCE_LIB})

