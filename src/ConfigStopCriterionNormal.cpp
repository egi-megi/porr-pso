//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#include "../include/ConfigStopCriterionNormal.h"

#include "../include/StopCriterionConfig.h"
#include "../include/Particle.h"

#include <math.h>

ConfigStopCriterionNormal::ConfigStopCriterionNormal(int mThreshold) :
    threshold(mThreshold)
{
    checksFallenBelowStopValue = 0;
}

bool ConfigStopCriterionNormal::computeStopCriterion(float criterionStopValue,
    const std::pair<Particle, Particle> &globalBestParticle)
{
    if (!globalBestParticle.second.isReady())
        return true;
    else if (globalBestParticle.second.getCostFunctionValue() -
        globalBestParticle.first.getCostFunctionValue() > criterionStopValue)
    {
        checksFallenBelowStopValue = 0;
        return true;
    }
    else
    {
        checksFallenBelowStopValue++;
        if(checksFallenBelowStopValue >= threshold)
            return false;
        else
            return true;
    }
}

void ConfigStopCriterionNormal::reset()
{
    checksFallenBelowStopValue = 0;
}