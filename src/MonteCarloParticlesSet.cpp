//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#include "../include/MonteCarloParticlesSet.h"
#include <random>

std::default_random_engine MonteCarloParticlesSet::generatorMC;

MonteCarloParticlesSet::MonteCarloParticlesSet(const int mVectorsDim, int mAmountOfParticles, int mNumberOfDraws, OptimizationExercisesConfig* config, float sigma, float tVariable)
{
    amountOfParticles = mAmountOfParticles;
    numberOfDraws = mNumberOfDraws;

    computeTheBestParticleMC(sigma, tVariable, config, mVectorsDim);
}

MonteCarloParticlesSet::~MonteCarloParticlesSet()
{
}

bool costFunSort(MonteCarloParticle p1, MonteCarloParticle p2) {
    return (p1.getCostFunctionValueMinMC() < p2.getCostFunctionValueMinMC());
}

MonteCarloParticle MonteCarloParticlesSet::computeTheBestParticleMC(float sigma, float tVariable, OptimizationExercisesConfig* config, const int mVectorsDim)
{
    //monteCarloParticlesVector.resize(amountOfParticles,0.0);
    for (int i = 0; i < amountOfParticles; i++) {
        MonteCarloParticle particleMC (mVectorsDim, *config, *generatorMC);
        for (int j = 0; j < numberOfDraws; j++) {
            particleMC.computePositionMC(sigma, tVariable);
        }
        monteCarloParticlesVector.push_back(particleMC);

    }
    std::sort(monteCarloParticlesVector.begin(), monteCarloParticlesVector.end(), costFunSort);
    return monteCarloParticlesVector[0];
}