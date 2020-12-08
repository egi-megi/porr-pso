//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/OptimizationExercisesConfig.h"

OptimizationExercisesConfig::OptimizationExercisesConfig(){
    lowerLimitPositionVector = -40;
    upperLimitPositionVector = 40;
};

OptimizationExercisesConfig::~OptimizationExercisesConfig() {};

bool OptimizationExercisesConfig::isXInRange(double position) {
    if (position > lowerLimitPositionVector && position < upperLimitPositionVector) {
        return true;
    } else {
        return false;
    }
}