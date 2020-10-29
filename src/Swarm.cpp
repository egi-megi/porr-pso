//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include <iostream>

using namespace std;

Swarm::Swarm(int mAmountOfParticles, int mVectorDim)
{
    amountOfParticles = mAmountOfParticles;
    vectorDim = mVectorDim;
    makeSwarm(amountOfParticles, vectorDim);
}

Swarm::~Swarm()
{
}

void Swarm::makeSwarm(int amountOfParticles, int vectorDim)
{
    for (int i = 0; i < amountOfParticles; i++)
    {
        Particle particle(vectorDim,this);
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


