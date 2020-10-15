 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles/include)
#add_subdirectory(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles)
# Define the OpenTuCo Module: Method/SCD

project(scd)

include_directories(include)
set(SOURCE_LIB include/selfconsistentmethod.h src/selfconsistentmethod.cpp
               include/crystaldipolemethod.h src/crystaldipolemethod.cpp
               include/clusterdipolemethod.h src/clusterdipolemethod.cpp)
	       #include/perturbationdipolemethod.h src/perturbationdipolemethod.cpp)
add_library(scd STATIC ${SOURCE_LIB})

