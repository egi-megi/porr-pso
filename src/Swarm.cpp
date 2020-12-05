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


#ifdef OPEN_MP


void Swarm::makeSwarm(OptimizationExercisesConfig* config)
{
    int i;
    int n = amountOfParticles;
    int s=swarm.size();
    std::default_random_engine* rand_engines[omp_get_num_procs()];
    for (int i=0 ; i<omp_get_num_procs(); i++) {
        rand_engines[i]=new std::default_random_engine();
        rand_engines[i]->seed(rand());
        cout<<"seed "<< i<<" " <<(*rand_engines[i])()<<"\n";
    }
    swarm.resize(s+n);
# pragma omp parallel for private(i) shared(n, swarm, rand_engines) //reduction (+: sum)
    {
        for (i = 0; i < n; i++) {
            Particle particle(vectorDim, this, config, (rand_engines[omp_get_thread_num ()]));
            swarm[s+i]=particle;
            //if (i < GbestVectorSize) {
              //  GbestVector.push_back(particle);
            //}
        }
    }
    for (int j = 0; j < GbestVectorSize; j++) {
        Particle particle(vectorDim, this, config,(rand_engines[0]));
        GbestVector.push_back(particle);
    }
    cout<<"particles omp done\n";
}

#else
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
#endif

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
        double  en=0;
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            singleParticle.computePosition(w, speedConstant1, speedConstant2);
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
            Swarm::computeGbest(&singleParticle);
            en+=singleParticle.getCostFunctionValue();
        }
      //  std::cout << "energia"<< en << std::endl;

        std::cout << GbestVector[0].costFunctionValuePbest << std::endl;
    }
    return GbestVector[0];

}

