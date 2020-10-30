//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include "../include/Particle.h"
#include "../include/Swarm.h"
#include <iostream>
#include <math.h>

using namespace std;
Particle::Particle() {}

Particle::Particle(int mVectorsDim, Swarm* s,std::function<double(vector<double>)> mfunctionToOptimize )
{
    vectorDim = mVectorsDim;
    functionToOptimize=mfunctionToOptimize;
    setStartPosition();
    computeCostFunctionValue();
    swarm = s;
    costFunctionValuePbest = costFunctionValue;
}

/*Particle::Particle(const Particle &particle)
{
    vectorDim = particle.vectorDim;
    positionVectors[vectorDim] = particle.positionVectors[vectorDim];
    speedVectors[vectorDim] = particle.speedVectors[vectorDim];
    Pbest[vectorDim] = particle.Pbest[vectorDim];
    Lbest[vectorDim] = particle.Lbest[vectorDim];
}*/

Particle::~Particle()
{
}


void Particle::setStartPosition()
{
    for (int i = 0; i < vectorDim; i++) {
        positionVectors.push_back(rand() % 80 - 40);
        speedVectors.push_back(rand() % 100);
    }
    positionVectorsParticlePbest = positionVectors;
}

void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2)
{
    for (int i = 0; i < vectorDim; i++) {
        double rand_1 = ((double) rand() / (RAND_MAX)) + 1;
        double rand_2 = ((double) rand() / (RAND_MAX)) + 1;
        double newSpeedValue = w * positionVectors[i] + speedConstant1 * rand_1 * (positionVectorsParticlePbest[i] - positionVectors[i]) + speedConstant2 + rand_2 * (swarm->Gbest->positionVectorsParticlePbest[i] - positionVectors[i]);
        speedVectors.push_back(newSpeedValue);
    }
}

void Particle::computePosition()
{
    for (int i = 0; i < vectorDim; i++) {
        double newPosition = positionVectors[i] + speedVectors[i];
        positionVectors[i] = newPosition;
    }
}

void Particle::computeCostFunctionValue()
{
    costFunctionValue = functionToOptimize(positionVectors);

}


void Particle::computeParticlePbest()
{
    if (costFunctionValue < costFunctionValuePbest) {
        costFunctionValuePbest = costFunctionValue;
        positionVectorsParticlePbest = positionVectors;
    }
}

double Particle::getParticlePbest()
{
    return particlePbest;
}

double Particle::getCostFunctionValuePbest()
{
    return costFunctionValuePbest;
}