//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H

#include <iostream>
#include <vector>

#include "SwarmParticle.h"
#include "ConfigStopCriterionAcademic.h"
#include "ConfigStopCriterionNormal.h"
#include "StopCriterionConfig.h"

using namespace std;

class Swarm
{
public:
    Swarm() = default;
    Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig *config);
    virtual ~Swarm() = default;

    void makeSwarm(OptimizationExercisesConfig *config);
    void computeGbest(SwarmParticle *particle);
    SwarmParticle findTheBestParticle(float criterionStopValue, float w, float speedConstant1,
        float speedConstant2, StopCriterionConfig *configStop);
    std::pair<SwarmParticle, SwarmParticle> globalBestParticle;

private:
    int amountOfParticles;
    int vectorDim;
    vector<SwarmParticle> swarm;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
