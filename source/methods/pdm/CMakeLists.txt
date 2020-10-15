 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

include_directories(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles/include)
#add_subdirectory(${CMAKE_SOURCE_DIR}/OpenPH/electrostatics/electricparticles)
# Define the OpenTuCo Module: Method/SCD

project(pdm)

include_directories(include)
set(SOURCE_LIB include/perturbationdipolemethod.h src/perturbationdipolemethod.cpp)
               #include/crystalperturbationmethod.h src/crystalperturbationmethod.cpp
               #include/clusterperturbationmethod.h src/clusterreturbationmethod.cpp)
add_library(pdm STATIC ${SOURCE_LIB})

