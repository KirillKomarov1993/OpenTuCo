 
cmake_minimum_required(VERSION 3.0.0)

# List internal includes needed.

#
# Define the OpenTuCo Module: Method/SSM

project(ssm)

include_directories(include)
set(SOURCE_LIB include/sequentialshiftmethod.h src/sequentialshiftmethod.cpp
               include/tunablepotential.h src/tunablepotential.cpp
	       include/configuration.h src/configuration.cpp
               include/dipolesequentialshiftmethod.h src/dipolesequentialshiftmethod.cpp
               include/bemsequentialshiftmethod.h src/bemsequentialshiftmethod.cpp)
add_library(ssm STATIC ${SOURCE_LIB})

