//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/OptimizationConfig.h"

bool OptimizationConfig::isXInRange(double position) {
    if (position > -40.0 || position < 40) {
        return true;
    } else {
        return false;
    }
}