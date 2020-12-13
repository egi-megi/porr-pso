//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>
#ifdef OPEN_MP_SWARM
#include <omp.h>
#endif

#include "../include/Swarm.h"
#include "../include/SwarmParticle.h"
#include "../include/Options.h"
#include "../include/Timer.h"

using namespace std;

Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig *config) :
    amountOfParticles{mAmountOfParticles}, vectorDim{mVectorDim}, swarm(mAmountOfParticles)
{
#ifdef OPEN_MP_SWARM
    printf("Welcome to OpenMP version!\n");
#else
    printf("Welcome to serial version!\n");
#endif
    Timer t1;
    makeSwarm(config);
    printf("Swarm::Swarm: Initialization took %.2lf s\n", t1.click());
}

Swarm::Swarm(Options* mOptions) :
    Swarm(mOptions->amountOfParticles, mOptions->dimension, mOptions->optimizationExerciseConfig)
{
    options = mOptions;
}

#ifdef OPEN_MP_SWARM
void Swarm::makeSwarm(OptimizationExercisesConfig *config)
{
#pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));
#pragma omp for
        for (int i = 0; i < amountOfParticles; i++)
        {
            SwarmParticle particle(vectorDim, this, config, &rand_engine);
            swarm[i] = particle;
        }
    }

    globalBestParticle.first = swarm[0];
    for (int i = 1; i < amountOfParticles; i++)
    {
        if (swarm[i].getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
            globalBestParticle.first = swarm[i];
    }
}
#else
void Swarm::makeSwarm(OptimizationExercisesConfig *config)
{
    std::default_random_engine rand_engine;
    rand_engine.seed(time(NULL));
    for (int i = 0; i < amountOfParticles; i++)
    {
        SwarmParticle particle(vectorDim, this, config, &rand_engine);
        swarm[i] = particle;
    }

    globalBestParticle.first = swarm[0];
    for (int i = 1; i < amountOfParticles; i++)
    {
        if (swarm[i].getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
            globalBestParticle.first = swarm[i];
    }
}
#endif

void Swarm::computeGbest(SwarmParticle *particle)
{
    if(particle == nullptr)
        return;
    else if (particle->getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
    {
        globalBestParticle.second = globalBestParticle.first;
        globalBestParticle.first = *particle;
    }
}

#ifdef OPEN_MP_SWARM
SwarmParticle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1,
    float speedConstant2, StopCriterionConfig *configStop)
{
    Timer t1;

    bool foundSolution = false;
    int iteration_number = 0;
#pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));

        SwarmParticle *bestParticleInIteration = nullptr;

        while (!foundSolution)
        {
#pragma omp for schedule(static)
            for (int i = 0; i < amountOfParticles; i++)
            {
                swarm[i].computePosition(w, speedConstant1, speedConstant2, &rand_engine);
                swarm[i].computeCostFunctionValue();
                swarm[i].computeParticlePbest();

                if (bestParticleInIteration == nullptr)
                    bestParticleInIteration = &swarm[i];
                else if (swarm[i].getCostFunctionValue() < bestParticleInIteration->getCostFunctionValue())
                    bestParticleInIteration = &swarm[i];
            }

#pragma omp critical
            computeGbest(bestParticleInIteration);
            bestParticleInIteration = nullptr;

#pragma omp barrier

#pragma omp master
            {
                printf("Swarm::findTheBestParticle: iteration = %d, globalBestParticle.first = %lf\n",
                       iteration_number, globalBestParticle.first.getCostFunctionValue());
                iteration_number++;
            }

#pragma omp critical
            {
                if (!configStop->computeStopCriterion(criterionStopValue, globalBestParticle))
                    foundSolution = true;
            }
        }
    }

    printf("Swarm::findTheBestParticle: Solution took %.2lf s\n", t1.click());

    return globalBestParticle.first;
}
#else
SwarmParticle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1,
    float speedConstant2, StopCriterionConfig *configStop)
{
    Timer t1;

    std::default_random_engine rand_engine;
    rand_engine.seed(time(NULL));

    int iteration_number = 0;
    while (configStop->computeStopCriterion(criterionStopValue, globalBestParticle))
    {
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            singleParticle.computePosition(w, speedConstant1, speedConstant2, &rand_engine);
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
            computeGbest(&singleParticle);
        }
        printf("Swarm::findTheBestParticle: iteration = %d, globalBestParticle.first = %lf\n",
               iteration_number, globalBestParticle.first.getCostFunctionValue());
        iteration_number++;
    }

    printf("Swarm::findTheBestParticle: Solution took %.2lf s\n", t1.click());

    return globalBestParticle.first;
}
#endif

SwarmParticle Swarm::findTheBestParticle(float w, float speedConstant1, float speedConstant2)
{
    return findTheBestParticle(options->stopCriterionThreshold, w, speedConstant1,
        speedConstant2, options->stopCriterionConfig);
}