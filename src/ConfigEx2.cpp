//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/OptimizationExercisesConfig.h"
#include "../include/ConfigEx2.h"
#include <math.h>

ConfigEx2::ConfigEx2() :OptimizationExercisesConfig()
{
    lowerLimit = -3.0;
    upperLimit = 3.0;
}

ConfigEx2::~ConfigEx2() {}

double ConfigEx2::computeCostFunctionValue(std::vector<double> positionVector)
{
    double costFunctionValue = 0.0;
    for (int i = 0; i < positionVector.size() - 1; i++) {
        costFunctionValue = costFunctionValue + (pow((positionVector[i + 1] - pow(positionVector[i], 2)), 2) * 100 + pow((1 -positionVector[i]), 2));
    }
    return costFunctionValue;
}

bool ConfigEx2::isPositionOK(std::vector<double> positionVector){
    double positionSum = 0;
    for (int i = 0; i < positionVector.size(); i++) // access by reference to avoid copying
    {
        positionSum = positionSum + pow((positionVector[i] - i + 1), 2);
    }
    if (positionSum <= positionVector.size() * 10) {
        return true;
    } else {
        return false;
    }
}


/*
bool ConfigEx2::isPositionOK(std::vector<double> positionVector){
    return true;
}*/
