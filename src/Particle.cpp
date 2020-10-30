//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include "../include/Particle.h"
#include "../include/Swarm.h"
#include <iostream>
#include <math.h>

using namespace std;

Particle::Particle(int mVectorsDim, Swarm* s)
{
    vectorDim = mVectorsDim;
    setStartPosition();
    computeCostFunctionValueZad2();
    swarm = s;
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
        positionVectors.push_back(newPosition);
    }
}

void Particle::computeCostFunctionValueZad()
{
    if (swarm->getExercisseNumber() == 1)
    {
        computeCostFunctionValueZad1();
    } else {
        computeCostFunctionValueZad2();
    }
}

void Particle::computeCostFunctionValueZad1()
{
    double suma = 0;
    double product = 1;
    for (int i = 0; i < vectorDim; i++) {
        suma = suma + pow(positionVectors[i], 2);
        product = product * cos(positionVectors[i]/i);
    }
    costFunctionValue = 1/40 * suma + 1 - product;

    costFunctionValuePbest = 10;
}

void Particle::computeCostFunctionValueZad2()
{
    costFunctionValue = 0.0;
    for (int i = 0; i < vectorDim - 1; i++) {
        costFunctionValue = costFunctionValue + (100 * pow((positionVectors[i + 1] - pow(positionVectors[i], 2)), 2) + (1 - pow(positionVectors[i], 2)));
    }
    costFunctionValuePbest = 10.0;
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