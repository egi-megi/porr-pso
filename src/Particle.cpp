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
        long t=rand();
        positionVectors.push_back(t% 80 - 40);
        t=rand();
        speedVectors.push_back(t % 100);
    }

    if (swarm->exerciseNumber == 2) {
        double positionSum = 0;
        for (int i = 0; i < positionVectors.size(); i++) // access by reference to avoid copying
        {
            positionSum = pow((positionVectors[i] - i + 1), 2);
        }
        while (positionSum > 10 * vectorDim) {
            positionVectors.clear();
            long t=rand();
            positionVectors.push_back(t% 80 - 40);
            positionSum = 0;
            for (int i = 0; i < positionVectors.size(); i++) // access by reference to avoid copying
            {
                positionSum = pow((positionVectors[i] - i + 1), 2);
            }
        }
    }

    positionVectorsParticlePbest = positionVectors;
}

void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2)
{
    vector <double> tempSpeedVector = speedVectors;
    speedVectors.clear();
    for (int i = 0; i < vectorDim; i++) {
        double rand_1 = ((double) rand() / (RAND_MAX)) + 1;
        double rand_2 = ((double) rand() / (RAND_MAX)) + 1;
        double newSpeedValue = w * tempSpeedVector[i] + speedConstant1 * rand_1 * (positionVectorsParticlePbest[i] - positionVectors[i]) + speedConstant2 + rand_2 * (swarm->Gbest->positionVectorsParticlePbest[i] - positionVectors[i]);
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

vector <double > Particle::getPositionVector()
{
    return positionVectors;
}

function<double(vector<double>)> Particle::getFunctionToOptimize()
{
    return functionToOptimize;
}