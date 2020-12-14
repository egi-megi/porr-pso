//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/ConfigEx2.h"

#include "../include/OptimizationExercisesConfig.h"

#include <math.h>

ConfigEx2::ConfigEx2() : OptimizationExercisesConfig() {}

ConfigEx2::~ConfigEx2() {}

double ConfigEx2::computeCostFunctionValue(std::vector<double> positionVector)
{
    double costFunctionValue = 0.0;
    for (unsigned int i = 0; i < positionVector.size() - 1; i++)
    {
        costFunctionValue = costFunctionValue + (pow((positionVector[i + 1] -
            pow(positionVector[i], 2)), 2) * 100 + pow((1 - positionVector[i]), 2));
    }
    return costFunctionValue;
}
