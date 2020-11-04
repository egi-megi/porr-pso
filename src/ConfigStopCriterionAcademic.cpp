//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#include "../include/ConfigStopCriterionAcademic.h"
#include "../include/StopCriterionConfig.h"
#include "../include/Particle.h"
#include <math.h>


bool ConfigStopCriterionAcademic::computeStopCriterion(float criterionStopValue, Particle *Gbest, Particle *GbestOld){
    double modelValueOfCostFunction = 0;
    if (Gbest->getCostFunctionValuePbest() - modelValueOfCostFunction > criterionStopValue) {
      return true;
    } else {
        return false;
    }
}