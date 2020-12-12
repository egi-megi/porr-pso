//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include "../include/Logger.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>

#ifdef OPEN_MP_SWARM
#include <omp.h>
#endif

using namespace std;

#ifdef OPEN_MP_SWARM
Swarm::Swarm(int mAmountOfParticles, int mVectorDim, Logger* log, OptimizationExercisesConfig* config) :
amountOfParticles{mAmountOfParticles}, vectorDim{mVectorDim}, swarm(mAmountOfParticles)
{
    log->stream << "$TYPE$" << '\n';   
    log->stream << "OpenMP" << '\n';
    log->stream << "$DATA$" << '\n';    
    printf("Welcome to OpenMP version!\n");    
    makeSwarm(config);
}
#else

Swarm::Swarm(int mAmountOfParticles, int mVectorDim, Logger* log, OptimizationExercisesConfig *config) :
amountOfParticles{mAmountOfParticles}, vectorDim{mVectorDim}, swarm(mAmountOfParticles)
{   
    log->stream << "$TYPE$" << '\n';   
    log->stream << "Serial" << '\n';
    log->stream << "$DATA$" << '\n';    
    printf("Welcome to serial version!\n");
    makeSwarm(config);
}

#endif

Swarm::~Swarm() {
}

#ifdef OPEN_MP_SWARM
void Swarm::makeSwarm(OptimizationExercisesConfig* config)
{
    #pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));
        printf("Thread %d: seed = %ld\n", omp_get_thread_num(), (omp_get_thread_num() + 1) * time(NULL));
        #pragma omp for
        for(int i = 0; i < amountOfParticles; i++) {
            Particle particle(vectorDim, this, config, &rand_engine);
            swarm[i] = particle;
        }
    }

    globalBestParticle.first = swarm[0];
    for(int i = 1; i < amountOfParticles; i++) {
        if(swarm[i].getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
            globalBestParticle.first = swarm[i];
    }
}

#else

void Swarm::makeSwarm(OptimizationExercisesConfig *config) {
    std::default_random_engine *random = new std::default_random_engine();
    (*random).seed(rand());
    for (int i = 0; i < amountOfParticles; i++) {
        Particle particle(vectorDim, this, config, random);
        swarm[i] = particle;
    }

    globalBestParticle.first = swarm[0];
    for(int i = 1; i < amountOfParticles; i++) {
        if(swarm[i].getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
            globalBestParticle.first = swarm[i];
    }
}

#endif


void Swarm::computeGbest(Particle *particle) {
    if(particle->getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue()) {
        globalBestParticle.second = globalBestParticle.first;
        globalBestParticle.first = *particle;
    }
}

#ifdef OPEN_MP_SWARM
Particle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2, Logger* log, StopCriterionConfig* configStop)
{
    bool foundSolution = false;
    int iteration_number = 0;
    #pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));
        printf("Thread %d: seed = %ld\n", omp_get_thread_num(), (omp_get_thread_num() + 1) * time(NULL));

        while (!foundSolution) {
            #pragma omp for schedule(dynamic, 1000) nowait
            for(int i = 0; i < amountOfParticles; i++) {
                swarm[i].computePosition(w, speedConstant1, speedConstant2, &rand_engine);
                swarm[i].computeCostFunctionValue();
                swarm[i].computeParticlePbest();
            }

            #pragma omp for
            for (auto &singleParticle : swarm) {
                #pragma omp critical
                Swarm::computeGbest(&singleParticle);
            }

            
            #pragma omp master
            {
                double cost = globalBestParticle.first.getCostFunctionValue();
                printf("Swarm::findTheBestParticle: iteration = %d, globalBestParticle.first = %lf\n",
                       iteration_number, cost);
                log->stream << iteration_number << ',' << cost << '\n';
                iteration_number++;
            }

#pragma omp critical
            {
                if(!configStop->computeStopCriterion(criterionStopValue, globalBestParticle))
                    foundSolution = true;
            }
        }
    }

    return globalBestParticle.first;
}

#else

Particle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2,
                                    Logger* log, StopCriterionConfig *configStop) {
    while (configStop->computeStopCriterion(criterionStopValue, &GbestVector)) {
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            singleParticle.computePosition(w, speedConstant1, speedConstant2);
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
        }
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            computeGbest(&singleParticle);
        }
    }

    return globalBestParticle.first;
}

#endif

