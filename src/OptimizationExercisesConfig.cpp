//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/OptimizationExercisesConfig.h"

OptimizationExercisesConfig::OptimizationExercisesConfig()
{
    lowerLimitPositionVector = -40;
    upperLimitPositionVector = 40;
};

bool OptimizationExercisesConfig::isXInRange(double position)
{
    if (position > lowerLimitPositionVector && position < upperLimitPositionVector)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool OptimizationExercisesConfig::isPositionInRange(std::vector<double> positionVector)
{
    for (unsigned int i = 0; i < positionVector.size(); i++)
    {
        if (positionVector[i] < lowerLimitPositionVector || positionVector[i] > upperLimitPositionVector)
        {
            printf("Position i = %d: %.16lf\n", i, positionVector[i]);
            return false;
        }
    }
    return true;
}