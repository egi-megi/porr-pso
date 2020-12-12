cmake_minimum_required(VERSION 2.8.12)
project(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if(APPLE)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)

    if(CMAKE_C_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_C_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang\$")
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY omp)
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Xpreprocessor -fopenmp -I/usr/local/include" )
endif()

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    add_definitions(-DOPEN_MP_SWARM)
endif()

add_executable(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski main.cpp
    include/ParticleBase.h src/ParticleBase.cpp
    src/Particle.cpp include/Particle.h
    include/Swarm.h src/Swarm.cpp
    include/OptimizationExercisesConfig.h src/ConfigEx1.cpp
    include/ConfigEx1.h src/ConfigEx2.cpp
    include/ConfigEx2.h src/OptimizationExercisesConfig.cpp
    src/StopCriterionConfig.cpp include/StopCriterionConfig.h
    src/ConfigStopCriterionAcademic.cpp include/ConfigStopCriterionAcademic.h
    src/ConfigStopCriterionNormal.cpp include/ConfigStopCriterionNormal.h
    src/PositionVectorOperator.cpp include/PositionVectorOperator.h)

if(APPLE)
    target_link_libraries(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski PRIVATE OpenMP::OpenMP_CXX -L/usr/local/opt/libomp/lib/)
else()
    target_link_libraries(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski PRIVATE OpenMP::OpenMP_CXX)
    #DWARF CONFIG
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -lgomp -l:libgomp.a")
    #target_link_libraries(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski PRIVATE -l:libgomp.a)
endif()