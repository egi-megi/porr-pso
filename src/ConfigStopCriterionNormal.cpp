//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#include "../include/ConfigStopCriterionNormal.h"

#include "../include/StopCriterionConfig.h"
#include "../include/Particle.h"

#include <math.h>

bool ConfigStopCriterionNormal::computeStopCriterion(float criterionStopValue,
    const std::pair<Particle, Particle> &globalBestParticle)
{
    if (!globalBestParticle.second.isReady())
        return true;
    else if (globalBestParticle.second.getCostFunctionValue() -
        globalBestParticle.first.getCostFunctionValue() > criterionStopValue)
    {
        return true;
    }
    else
    {
        return false;
    }
}