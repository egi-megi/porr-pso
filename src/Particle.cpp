//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include "../include/Particle.h"
#include <iostream>

using namespace std;

Particle::Particle(int mVectorsDim)
{
    vectorDim = mVectorsDim;
    Particle::setStartPosition();
    speedVectors[vectorDim] = {0};
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

void Particle::setVectorDim(int mVectorDim)
{
    vectorDim = mVectorDim;
}

int Particle::getVectorDim()
{
    return vectorDim;
}

void Particle::setStartPosition()
{
    for (int i = 0; i < vectorDim; i++) {
        positionVectors.push_back(rand() % 80 - 40);
    }
}

void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2)
{
    for (int i = 0; i < vectorDim; i++) {
        double rand_1 = ((double) rand() / (RAND_MAX)) + 1;
        double rand_2 = ((double) rand() / (RAND_MAX)) + 1;
        double newSpeedValue = w * positionVectors[i] + speedConstant1 * rand_1 * (Pbest - positionVectors[i]) + speedConstant2 + rand_2 * (Lbest - positionVectors[i]);
        positionVectors.push_back(newSpeedValue);
    }
}

void Particle::computePosition()
{
    for (int i = 0; i < vectorDim; i++) {
        double newPosition = positionVectors[i] + speedVectors[i];
        positionVectors.push_back(newPosition);
    }
}