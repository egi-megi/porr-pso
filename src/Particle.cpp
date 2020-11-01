//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include "../include/Particle.h"
#include "../include/Swarm.h"
#include <iostream>
#include <math.h>

using namespace std;
Particle::Particle() {}

Particle::Particle(const int mVectorsDim, Swarm* s,OptimizationConfig* mconfig )
{
    vectorDim = mVectorsDim;
    speedVectors.resize(mVectorsDim,0.0);
    tempSpeedVectors.resize(mVectorsDim, 0.0);
    positionVectors.resize(mVectorsDim,0.0);
    config=mconfig;
    setStartPosition();
    setStartSpeed();
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
    do {
    for (int i = 0; i < vectorDim; i++) {
        long t=rand();
        positionVectors[i] = t% 6- 3;
    }
    } while (! config->isPositionOK(positionVectors));

    positionVectorsParticlePbest = positionVectors;
}

void Particle::setStartSpeed() {
    for (int i = 0; i < vectorDim; i++) {
        long t = rand();
        speedVectors[i] = t % 100;
    }
}

void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2, int i)
{
    for (int i = 0; i < vectorDim; i++) {
        double rand_1 = ((double) rand() / (RAND_MAX)) + 1;
        double rand_2 = ((double) rand() / (RAND_MAX)) + 1;
        double tempSpeedValue =
                w * speedVectors[i] + speedConstant1 * rand_1 * (positionVectorsParticlePbest[i] - positionVectors[i]) +
                speedConstant2 + rand_2 * (swarm->Gbest->positionVectorsParticlePbest[i] - positionVectors[i]);
        tempSpeedVectors[i] = tempSpeedValue;
    }
}

void Particle::computePosition(float w, float speedConstant1, float speedConstant2)
{
    vector <double> newPositionVector;
    newPositionVector.resize(vectorDim,0.0);
    do {
        for (int i = 0; i < vectorDim; i++) {
            do {
                computeSpeed(w, speedConstant1, speedConstant2, i);
                newPositionVector[i] = positionVectors[i] + tempSpeedVectors[i];
            }  while (! config->isXInRange(newPositionVector[i]));
        }
    } while (! config->isPositionOK(newPositionVector));
    speedVectors = tempSpeedVectors;
    positionVectors = newPositionVector;
}

void Particle::computeCostFunctionValue()
{
    costFunctionValue = config->computeCostFunctionValue(positionVectors);
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

vector <double > Particle::getPositionVector()
{
    return positionVectors;
}
