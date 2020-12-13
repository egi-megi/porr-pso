#include "../include/Swarm.h"

#include "../include/SwarmParticle.h"
#include "../include/Options.h"
#include "../include/Timer.h"

#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>
#ifdef OPEN_MP_SWARM
#include <omp.h>
#endif

using namespace std;

Swarm::Swarm(Options* mOptions) :
    amountOfParticles{mOptions->amountOfParticles}, vectorDim{mOptions->dimension},
    swarm(mOptions->amountOfParticles), options{mOptions}
{
#ifdef OPEN_MP_SWARM
    printf("Welcome to OpenMP version!\n");
#else
    printf("Welcome to serial version!\n");
#endif
    Timer t1;
    makeSwarm();
    if(options->timing)
        printf("Swarm::Swarm: Initialization took %.2lf s\n", t1.click());
}

#ifdef OPEN_MP_SWARM
void Swarm::makeSwarm()
{
#pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));
#pragma omp for
        for (int i = 0; i < amountOfParticles; i++)
        {
            SwarmParticle particle(options, this, &rand_engine);
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
void Swarm::makeSwarm()
{
    std::default_random_engine rand_engine;
    rand_engine.seed(time(NULL));
    for (int i = 0; i < amountOfParticles; i++)
    {
        SwarmParticle particle(options, this, &rand_engine);
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
            if(options->communication == Options::CommunicationType::LOCAL_BEST)
            {
                swarm[0].setLocalBestParticleVisiblePosition(
                    getPositionOfBetterParticle(
                        swarm[amountOfParticles - 1], swarm[1]
                    )
                );
                swarm[amountOfParticles - 1].setLocalBestParticleVisiblePosition(
                    getPositionOfBetterParticle(
                        swarm[amountOfParticles - 2],
                        swarm[0]
                    )
                );
#pragma omp for schedule(static)
                for(int i = 1; i < amountOfParticles - 1; i++)
                    swarm[i].setLocalBestParticleVisiblePosition(
                        getPositionOfBetterParticle(
                            swarm[i-1],
                            swarm[i+1]
                        )
                    );
            }
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
                if(options->verbose)
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

    if(options->timing)
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
        if(options->communication == Options::CommunicationType::LOCAL_BEST)
        {
            swarm[0].setLocalBestParticleVisiblePosition(
                getPositionOfBetterParticle(
                    swarm[amountOfParticles - 1], swarm[1]
                )
            );
            swarm[amountOfParticles - 1].setLocalBestParticleVisiblePosition(
                getPositionOfBetterParticle(
                    swarm[amountOfParticles - 2],
                    swarm[0]
                )
            );
            for(int i = 1; i < amountOfParticles - 1; i++)
                swarm[i].setLocalBestParticleVisiblePosition(
                    getPositionOfBetterParticle(
                        swarm[i-1],
                        swarm[i+1]
                    )
                );
        }
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            singleParticle.computePosition(w, speedConstant1, speedConstant2, &rand_engine);
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
            computeGbest(&singleParticle);
        }
        if(options->verbose)
            printf("Swarm::findTheBestParticle: iteration = %d, globalBestParticle.first = %lf\n",
                iteration_number, globalBestParticle.first.getCostFunctionValue());
        iteration_number++;
    }

    if(options->timing)
        printf("Swarm::findTheBestParticle: Solution took %.2lf s\n", t1.click());

    return globalBestParticle.first;
}
#endif

SwarmParticle Swarm::findTheBestParticle(float w, float speedConstant1, float speedConstant2)
{
    return findTheBestParticle(options->stopCriterionThreshold, w, speedConstant1,
        speedConstant2, options->stopCriterionConfig);
}

vector<double> Swarm::getPositionOfBetterParticle(SwarmParticle& p_1, SwarmParticle& p_2)
{
    if(p_1.getCostFunctionValue() < p_2.getCostFunctionValue())
        return p_1.getPositionVector();
    else
        return p_2.getPositionVector();
}