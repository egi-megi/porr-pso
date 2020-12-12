//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#include "../include/ConfigStopCriterionAcademic.h"
#include "../include/StopCriterionConfig.h"
#include "../include/Particle.h"
#include <math.h>



bool ConfigStopCriterionAcademic::computeStopCriterion(float criterionStopValue, const std::pair<Particle, Particle>& globalBestParticle){
    double modelValueOfCostFunction = 0;
    if (globalBestParticle.first.getCostFunctionValue() - modelValueOfCostFunction > criterionStopValue) {
      return true;
    } else {
        return false;
    }
}