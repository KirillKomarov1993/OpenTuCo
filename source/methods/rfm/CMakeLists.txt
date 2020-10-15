 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

project(rfm)

include_directories(include)
set(SOURCE_LIB include/reactionfieldmethod.h src/reactionfieldmethod.cpp)

add_library(rfm STATIC ${SOURCE_LIB})

