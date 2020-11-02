//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/OptimizationExercisesConfig.h"

OptimizationExercisesConfig::OptimizationExercisesConfig()
{
}

OptimizationExercisesConfig::~OptimizationExercisesConfig() {};

bool OptimizationExercisesConfig::isXInRange(double position) {
    if (position > lowerLimit || position < upperLimit) {
        return true;
    } else {
        return false;
    }
}