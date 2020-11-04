//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#include "../include/ConfigStopCriterionNormal.h"
#include "../include/StopCriterionConfig.h"
#include "../include/Particle.h"
#include <math.h>


bool ConfigStopCriterionNormal::computeStopCriterion(float criterionStopValue, Particle *Gbest, Particle *GbestOld){
    if (Gbest->getCostFunctionValuePbest() - GbestOld->getCostFunctionValuePbest() > criterionStopValue) {
        return true;
    } else {
        return false;
    }
}