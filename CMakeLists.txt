cmake_minimum_required(VERSION 3.15)
project(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski)

set(CMAKE_CXX_STANDARD 14)

add_executable(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski main.cpp src/Particle.cpp include/Particle.h include/Swarm.h src/Swarm.cpp include/OptimizationExercisesConfig.h src/ConfigEx1.cpp include/ConfigEx1.h src/ConfigEx2.cpp include/ConfigEx2.h src/OptimizationExercisesConfig.cpp src/StopCriterionConfig.cpp include/StopCriterionConfig.h src/ConfigStopCriterionAcademic.cpp include/ConfigStopCriterionAcademic.h src/ConfigStopCriterionNormal.cpp include/ConfigStopCriterionNormal.h)