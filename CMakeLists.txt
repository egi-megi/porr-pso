cmake_minimum_required(VERSION 3.15)
project(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski)

set(CMAKE_CXX_STANDARD 14)

add_executable(rojCzastek_Szczepanski_Jurkiewicz_Pikulinski main.cpp src/Particle.cpp include/Particle.h include/Swarm.h src/Swarm.cpp include/OptimizationConfig.h src/ConfigEx1.cpp include/ConfigEx1.h)