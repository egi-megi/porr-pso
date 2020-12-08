//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#include "../include/ConfigStopCriterionNormal.h"
#include "../include/StopCriterionConfig.h"
#include "../include/Particle.h"
#include <math.h>


bool ConfigStopCriterionNormal::computeStopCriterion(float criterionStopValue, vector <Particle> * GbestVector){
    if ((*GbestVector)[0].getCostFunctionValuePbest() - (*GbestVector)[(*GbestVector).size() - 1].getCostFunctionValuePbest() > criterionStopValue) {
        return true;
    } else {
        return false;
    }
}