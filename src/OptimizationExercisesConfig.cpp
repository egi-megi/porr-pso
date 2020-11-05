//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/OptimizationExercisesConfig.h"

OptimizationExercisesConfig::OptimizationExercisesConfig(double lowerLimit, double upperLimit) : lowerLimitPositionVector( lowerLimit ), upperLimitPositionVector (upperLimit) {};

OptimizationExercisesConfig::~OptimizationExercisesConfig() {};

bool OptimizationExercisesConfig::isXInRange(double position) {
    if (position > lowerLimitPositionVector || position < upperLimitPositionVector) {
        return true;
    } else {
        return false;
    }
}