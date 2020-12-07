//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;

#ifdef OPEN_MP
Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig* config)
{
    amountOfParticles = mAmountOfParticles;
    vectorDim = mVectorDim;

    makeSwarm(config);
    std::cout << "Open_MP\n";
    std::cout << "Num proc" << omp_get_num_procs()<<"\n";
}
#else
Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig* config)
{
    amountOfParticles = mAmountOfParticles;
    vectorDim = mVectorDim;

    makeSwarm(config);
}
#endif

Swarm::~Swarm()
{
}

void Swarm::makeSwarm(OptimizationExercisesConfig* config)
{
    for (int i = 0; i < amountOfParticles; i++)
    {
        Particle particle(vectorDim,this,config);
        swarm.push_back(particle);
        if (i < GbestVectorSize) {
            GbestVector.push_back(particle);
        }
    }
}


void Swarm::computeGbest(Particle *particle)
{
int j = 0;
    while (GbestVector[j].getCostFunctionValuePbest() < particle->getCostFunctionValuePbest() && j < GbestVector.size()) {
        j++;
    }
    if (j < GbestVector.size()) {
        for (int i = GbestVector.size() - 1; i > j; i--) {
            GbestVector[i] = GbestVector[i -1];
        }
        GbestVector[j] = *particle;
    }
}

#ifdef OPEN_MP
Particle Swarm::findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2, StopCriterionConfig *configStop)
{
    std::default_random_engine* rand_engines[omp_get_num_procs()];
    for (int j=0 ; j<omp_get_num_procs(); j++) {
        rand_engines[j]=new std::default_random_engine();
        rand_engines[j]->seed(rand());
        cout<<"seed "<< j<<" " <<(*rand_engines[j])()<<"\n";
    }
    while (configStop->computeStopCriterion(criterionStopValue, GbestVector))
    {
        int i;
# pragma omp parallel for private(i, w, speedConstant1, speedConstant2) shared(swarm, rand_engines) //reduction (+: sum)
        {
            for (i = 0; i < swarm.size(); i++) {
                swarm[i].computePosition(w, speedConstant1, speedConstant2, (rand_engines[omp_get_thread_num ()]));
                swarm[i].computeCostFunctionValue();
                swarm[i].computeParticlePbest();
            }
        }

        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            Swarm::computeGbest(&singleParticle);
        }
        std::cout << GbestVector[0].costFunctionValuePbest << std::endl;
    }
    return GbestVector[0];
}
#else
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
        }

        std::cout << GbestVector[0].costFunctionValuePbest << std::endl;
    }
    return GbestVector[0];
}
#endif

