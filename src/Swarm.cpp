//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include <iostream>

using namespace std;

Swarm::Swarm(int mAmountOfParticles, int mVectorDim, std::function<double(vector<double>)> mfunctionToOptimize )
{
    amountOfParticles = mAmountOfParticles;
    vectorDim = mVectorDim;

    makeSwarm(amountOfParticles, vectorDim,mfunctionToOptimize);
}

Swarm::~Swarm()
{
}

void Swarm::makeSwarm(int amountOfParticles, int vectorDim, std::function<double(vector<double>)> mfunctionToOptimize )
{
    for (int i = 0; i < amountOfParticles; i++)
    {
        Particle particle(vectorDim,this,mfunctionToOptimize);
        swarm.push_back(particle);
    }
    Gbest = &swarm.front();
}


void Swarm::computeGbest(Particle *particle)
{
    if (Gbest->getCostFunctionValuePbest() > particle->getCostFunctionValuePbest())
    {
        Gbest = particle;
    }
}

Particle Swarm::findTheBestParticle(float academicCondition, float w, float speedConstant1, float speedConstant2)
{
    double modelValueOfCostFunction = 0;
    while (Gbest->getCostFunctionValuePbest() - modelValueOfCostFunction > academicCondition)
    {
        for (auto &singleParticle : swarm) // access by reference to avoid copying
        {
            singleParticle.computeSpeed(w, speedConstant1, speedConstant2);
            singleParticle.computePosition();
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
            Swarm::computeGbest(&singleParticle);
            std::cout << Gbest->costFunctionValuePbest << std::endl;
        }
    }
    return *Gbest;

}


