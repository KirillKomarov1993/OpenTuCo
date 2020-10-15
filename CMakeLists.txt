cmake_minimum_required(VERSION 3.0.0)

project(OpenTuCo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

#find_package(Qt5Core)

# Define of the OpenPH:

include_directories(OpenPH/math/algebra/include)
include_directories(OpenPH/math/mathlist/include)
include_directories(OpenPH/phys/physlist/include)
include_directories(OpenPH/statphys/include)
include_directories(OpenPH/electrostatics/values/include)
include_directories(OpenPH/electrostatics/electricfields/include)
include_directories(OpenPH/electrostatics/electricparticles/include)
include_directories(OpenPH/electrostatics/kernals/include)
include_directories(OpenPH/electrostatics/values/include)

add_subdirectory(OpenPH/math/algebra)
add_subdirectory(OpenPH/math/mathlist)
add_subdirectory(OpenPH/phys/physlist)
add_subdirectory(OpenPH/statphys)
add_subdirectory(OpenPH/electrostatics/electricfields)
add_subdirectory(OpenPH/electrostatics/electricparticles)
add_subdirectory(OpenPH/electrostatics/kernals)
add_subdirectory(OpenPH/electrostatics/values)

# Define of the OpenPH:

include_directories(OpenCS/crystals/include)
include_directories(OpenCS/structures/include)
include_directories(OpenCS/deformationmethods/include)
include_directories(OpenCS/optimizer/include)
include_directories(OpenCS/resiprocalspace/include)
add_subdirectory(OpenCS/crystals)
add_subdirectory(OpenCS/structures)
add_subdirectory(OpenCS/deformationmethods)
add_subdirectory(OpenCS/optimizer)
add_subdirectory(OpenCS/resiprocalspace)

# Define of the OpenPhonon:

include_directories(OpenPhonon/phonon/include)
include_directories(OpenPhonon/methods/bvk/include)
include_directories(OpenPhonon/atomcrystal/include)
add_subdirectory(OpenPhonon/phonon)
add_subdirectory(OpenPhonon/methods/bvk)
add_subdirectory(OpenPhonon/atomcrystal)

# Define of the OpenPR:

include_directories(OpenPR/processing/include)
add_subdirectory(OpenPR/processing)


# Define of this library (OpenTuCo):

include_directories(source/geometry/space/include)
include_directories(source/geometry/mesh/include)
include_directories(source/geometry/shapes/include)
include_directories(source/geometry/surfaces/include)
include_directories(source/geometry/curves/include)
include_directories(source/materials/include)
include_directories(source/particles/include)
include_directories(source/hamiltanian/include)
include_directories(source/systems/include)
#include_directories(source/physmodels/disperisons/include)
include_directories(source/physmodels/electricmodels/include)
include_directories(source/integralequations/include)
include_directories(source/integration/include)
include_directories(source/boundaryelements/include)
include_directories(source/methods/scd/include)
include_directories(source/methods/bem/include)
include_directories(source/methods/eem/include)
#include_directories(source/methods/pdm/include)
include_directories(source/methods/ssm/include)
include_directories(source/methods/rfm/include)
include_directories(source/methods/tucomethods/include)

#set(SOURCES main.cpp)
#add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(main main.cpp)



add_subdirectory(source/geometry/space)
add_subdirectory(source/geometry/mesh)
add_subdirectory(source/geometry/shapes)
add_subdirectory(source/geometry/surfaces)
add_subdirectory(source/geometry/curves)
add_subdirectory(source/materials)
add_subdirectory(source/particles)
add_subdirectory(source/hamiltanian)
add_subdirectory(source/systems)
#add_subdirectory(source/physmodels/disperisons)
add_subdirectory(source/physmodels/electricmodels)
add_subdirectory(source/integralequations)
add_subdirectory(source/integration)
add_subdirectory(source/boundaryelements)
add_subdirectory(source/methods/scd)
add_subdirectory(source/methods/bem)
add_subdirectory(source/methods/eem)
#add_subdirectory(source/methods/pdm)
add_subdirectory(source/methods/ssm)
add_subdirectory(source/methods/rfm)
add_subdirectory(source/methods/tucomethods)

#target_link_libraries(main
#                           space mathlist physlist mesh shapes kernals)


target_link_libraries(main  bvk
                            phonon
                            atomcrystal
                            processing
                            optimizer
                            deformationmethods
                            rfm
                            ssm
                            eem
                            bem                            
                            scd
                            electricmodels
                            tucomethods
                            systems
                            hamiltanian
                            electricparticles
                            colloids
                            integralequation
                            integration
                            boundaryelements
                            shapes
                            surfaces
                            curves
                            mesh
                            space
                            materials
                            resiprocalspace
                            structures
                            crystals
                            electricfields
                            values
                            kernals
                            statphys
                            physlist
                            algebra
                            mathlist
                            fftw3)






