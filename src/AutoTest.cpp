#include "../include/AutoTest.h"

void processTestCombination(TEST val) 
{   
    Parameters params;

    switch (val) {
	case TEST::S1AP: params = Parameters {"Swarm", "Task1", "Academic", "Parallel"}; break;
    case TEST::S1NP: params = Parameters {"Swarm", "Task1", "Normal", "Parallel"}; break;
    case TEST::MC1AP: params = Parameters {"MonteCarlo", "Task1", "Academic", "Parallel"}; break;
    case TEST::MC1NP: params = Parameters {"MonteCarlo", "Task1", "Normal", "Parallel"}; break;
    case TEST::S2AP: params = Parameters {"Swarm", "Task2", "Academic", "Parallel"}; break;
    case TEST::S2NP: params = Parameters {"Swarm", "Task2", "Normal", "Parallel"}; break;
    case TEST::MC2AP: params = Parameters {"MonteCarlo", "Task2", "Academic", "Parallel"}; break;
    case TEST::MC2NP: params = Parameters {"MonteCarlo", "Task2", "Normal", "Parallel"}; break;
    case TEST::S1AS: params = Parameters {"Swarm", "Task1", "Academic", "Serial"}; break;
    case TEST::S1NS: params = Parameters {"Swarm", "Task1", "Normal", "Serial"}; break;
    case TEST::MC1AS: params = Parameters {"MonteCarlo", "Task1", "Academic", "Serial"}; break;
    case TEST::MC1NS: params = Parameters {"MonteCarlo", "Task1", "Normal", "Serial"}; break;
    case TEST::S2AS: params = Parameters {"Swarm", "Task2", "Academic", "Serial"}; break;
    case TEST::S2NS: params = Parameters {"Swarm", "Task2", "Normal", "Serial"}; break;
    case TEST::MC2AS: params = Parameters {"MonteCarlo", "Task2", "Academic", "Serial"}; break;
    case TEST::MC2NS: params = Parameters {"MonteCarlo", "Task2", "Normal", "ParaSerialllel"}; break;
    }

} 

Combination::Combination(Parameters params) : algorithm(params[0]), task(params[1]), stopCondition(params[2]), cpuBehaviour(params[3])
{    
}

Combination::Combination(TEST testId) 
{
    Parameters params;

    switch (testId) {
	case TEST::S1AP: params = Parameters {"Swarm", "Task1", "Academic", "Parallel"}; break;
    case TEST::S1NP: params = Parameters {"Swarm", "Task1", "Normal", "Parallel"}; break;
    case TEST::MC1AP: params = Parameters {"MonteCarlo", "Task1", "Academic", "Parallel"}; break;
    case TEST::MC1NP: params = Parameters {"MonteCarlo", "Task1", "Normal", "Parallel"}; break;
    case TEST::S2AP: params = Parameters {"Swarm", "Task2", "Academic", "Parallel"}; break;
    case TEST::S2NP: params = Parameters {"Swarm", "Task2", "Normal", "Parallel"}; break;
    case TEST::MC2AP: params = Parameters {"MonteCarlo", "Task2", "Academic", "Parallel"}; break;
    case TEST::MC2NP: params = Parameters {"MonteCarlo", "Task2", "Normal", "Parallel"}; break;
    case TEST::S1AS: params = Parameters {"Swarm", "Task1", "Academic", "Serial"}; break;
    case TEST::S1NS: params = Parameters {"Swarm", "Task1", "Normal", "Serial"}; break;
    case TEST::MC1AS: params = Parameters {"MonteCarlo", "Task1", "Academic", "Serial"}; break;
    case TEST::MC1NS: params = Parameters {"MonteCarlo", "Task1", "Normal", "Serial"}; break;
    case TEST::S2AS: params = Parameters {"Swarm", "Task2", "Academic", "Serial"}; break;
    case TEST::S2NS: params = Parameters {"Swarm", "Task2", "Normal", "Serial"}; break;
    case TEST::MC2AS: params = Parameters {"MonteCarlo", "Task2", "Academic", "Serial"}; break;
    case TEST::MC2NS: params = Parameters {"MonteCarlo", "Task2", "Normal", "ParaSerialllel"}; break;
    }
    updateConfiguration(params);
}

void Combination::updateConfiguration(const Parameters& params) 
{
    algorithm=params[0];
    task=params[1];
    stopCondition=params[2];
    cpuBehaviour=params[3];
}
