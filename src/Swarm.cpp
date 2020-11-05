//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include <iostream>
#include <math.h>

using namespace std;

Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig* config)
{
    amountOfParticles = mAmountOfParticles;
    vectorDim = mVectorDim;

    makeSwarm(amountOfParticles, vectorDim, config);
}

Swarm::~Swarm()
{
}

void Swarm::makeSwarm(int amountOfParticles, int vectorDim, OptimizationExercisesConfig* config)
{
    for (int i = 0; i < amountOfParticles; i++)
    {
        Particle particle(vectorDim,this,config);
        swarm.push_back(particle);
        if (i < 10) {
            GbestVector.push_back(particle);
        }
    }
}


void Swarm::computeGbest(Particle *particle)
{
    if (GbestVector[0].getCostFunctionValuePbest() > particle->getCostFunctionValuePbest())
    {
        for (int i = GbestVector.size() - 1; i < 0; i--) {
            GbestVector[i] = GbestVector[i -1];
        }
        GbestVector[0] = *particle;
    }
}

Particle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2, StopCriterionConfig *configStop)
{
    while (configStop->computeStopCriterion(criterionStopValue, GbestVector))
    {
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            singleParticle.computePosition(w, speedConstant1, speedConstant2);
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
            Swarm::computeGbest(&singleParticle);
            std::cout << GbestVector[0].costFunctionValuePbest << std::endl;
        }
    }
    return GbestVector[0];

}


