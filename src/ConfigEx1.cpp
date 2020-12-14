//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/ConfigEx1.h"

#include "../include/OptimizationExercisesConfig.h"

#include <math.h>

ConfigEx1::ConfigEx1() : OptimizationExercisesConfig() {}

ConfigEx1::~ConfigEx1() {}

double ConfigEx1::computeCostFunctionValue(std::vector<double> positionVector)
{
    double suma = 0;
    double product = 1;
    for (unsigned int i = 0; i < positionVector.size(); i++)
    {
        suma = suma + pow(positionVector[i], 2);
        product = product * cos(positionVector[i] / (i + 1));
    }
    return 1.0 / 40 * suma + 1 - product;
}
