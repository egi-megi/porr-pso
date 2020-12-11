//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>

#ifdef OPEN_MP_SWARM
#include <omp.h>
#endif

using namespace std;

#ifdef OPEN_MP_SWARM
Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig* config) :
amountOfParticles{mAmountOfParticles}, vectorDim{mVectorDim}, swarm{(long unsigned int) mAmountOfParticles}
{
    printf("Welcome to OpenMP version!\n");
    makeSwarm(config);
}
#else

Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig *config) :
amountOfParticles{mAmountOfParticles}, vectorDim{mVectorDim}, swarm{(long unsigned int) mAmountOfParticles}
{
    printf("Welcome to serial version!\n");
    makeSwarm(config);
}

#endif

Swarm::~Swarm() {
}

bool gbestSort(Particle p1, Particle p2) {
    return (p1.getCostFunctionValuePbest() < p2.getCostFunctionValuePbest());
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

    for (int j = 0; j < GbestVectorSize; j++) {
		GbestVector.push_back(swarm[j]);
	}
	std::sort(GbestVector.begin(), GbestVector.end(), gbestSort);
}

#else

void Swarm::makeSwarm(OptimizationExercisesConfig *config) {
    std::default_random_engine *random = new std::default_random_engine();
    (*random).seed(rand());
    for (int i = 0; i < amountOfParticles; i++) {
        Particle particle(vectorDim, this, config, random);
        swarm[i] = particle;
    }
    for (int j = 0; j < GbestVectorSize; j++) {
        GbestVector.push_back(swarm[j]);
    }
    std::sort(GbestVector.begin(), GbestVector.end(), gbestSort);
}

#endif


void Swarm::computeGbest(Particle *particle) {
    unsigned int j = 0;
    while (j < GbestVector.size() &&
           GbestVector[j].getCostFunctionValuePbest() < particle->getCostFunctionValuePbest()) {
        j++;
    }
    if (j < GbestVector.size()) {
        for (unsigned int i = GbestVector.size() - 1; i > j; i--) {
            GbestVector[i] = GbestVector[i - 1];
        }
        GbestVector[j] = *particle;
    }
}

#ifdef OPEN_MP_SWARM
Particle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2, StopCriterionConfig* configStop)
{
    bool foundSolution = false;
    #pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));
        printf("Thread %d: seed = %ld\n", omp_get_thread_num(), (omp_get_thread_num() + 1) * time(NULL));

        while (!foundSolution) {
            #pragma omp for schedule(dynamic, 1000)
            for(int i = 0; i < amountOfParticles; i++) {
                swarm[i].computePosition(w, speedConstant1, speedConstant2, &rand_engine);
                swarm[i].computeCostFunctionValue();
                swarm[i].computeParticlePbest();
            }

            #pragma omp for ordered
            for (auto &singleParticle : swarm) {
                Swarm::computeGbest(&singleParticle);
            }

            if(omp_get_thread_num() == 0)
                printf("Swarm::findTheBestParticle: New Gbest = %lf\n", GbestVector[0].costFunctionValuePbest);

            #pragma omp critical
            {
                if(!configStop->computeStopCriterion(criterionStopValue, &GbestVector))
                    foundSolution = true;
            } 
        }
    }

    return GbestVector[0];
}

#else

Particle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2,
                                    StopCriterionConfig *configStop) {
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
        std::cout << GbestVector[0].costFunctionValuePbest << std::endl;
    }
    return GbestVector[0];
}

#endif

