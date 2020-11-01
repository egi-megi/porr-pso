//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//
#include "../include/Swarm.h"
#include "../include/Particle.h"
#include <iostream>
#include <math.h>

using namespace std;

Swarm::Swarm(int mAmountOfParticles, int mVectorDim, OptimizationConfig* config, int mExerciseNumber)
{
    exerciseNumber = mExerciseNumber;
    amountOfParticles = mAmountOfParticles;
    vectorDim = mVectorDim;

    makeSwarm(amountOfParticles, vectorDim, config);
}

Swarm::~Swarm()
{
}

void Swarm::makeSwarm(int amountOfParticles, int vectorDim, OptimizationConfig* config)
{
    for (int i = 0; i < amountOfParticles; i++)
    {
        Particle particle(vectorDim,this,config);
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
            if (exerciseNumber == 2) {
                double positionSum = 0;
                for (int i = 0; i < vectorDim; i++) // access by reference to avoid copying
                {
                    positionSum = pow((singleParticle.getPositionVector()[i] - i + 1), 2);
                }
                while (positionSum > 1000 * vectorDim) {
                    singleParticle.computeSpeed(w, speedConstant1, speedConstant2);
                    singleParticle.computePosition();
                    positionSum = 0;
                    for (int i = 0; i < vectorDim; i++) // access by reference to avoid copying
                    {
                        positionSum = pow((singleParticle.getPositionVector()[i] - i + 1), 2);
                    }
                }
            }
            singleParticle.computeCostFunctionValue();
            singleParticle.computeParticlePbest();
            Swarm::computeGbest(&singleParticle);
            std::cout << Gbest->costFunctionValuePbest << std::endl;
        }
    }
    return *Gbest;

}


