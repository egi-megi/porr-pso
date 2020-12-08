//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include "../include/Particle.h"
#include "../include/Swarm.h"
#include <iostream>
#include <math.h>
#include <random>
//#include <omp.h>

using namespace std;


Particle::Particle() {}

Particle::Particle(const int mVectorsDim, Swarm *s, OptimizationExercisesConfig *mconfig,
                   std::default_random_engine *gen) {
    vectorDim = mVectorsDim;
    generator = gen;
    speedVectors.resize(mVectorsDim, 0.0);
    tempSpeedVectors.resize(mVectorsDim, 0.0);
    positionVectors.resize(mVectorsDim, 0.0);
    config = mconfig;
    setStartPosition();
    setStartSpeed();
    computeCostFunctionValue();
    swarm = s;
    costFunctionValuePbest = costFunctionValue;
}

Particle::~Particle() {
}


void Particle::setStartPosition() {
    std::uniform_real_distribution<double> unif(config->lowerLimitPositionVector, config->upperLimitPositionVector);
    for (int i = 0; i < vectorDim; i++) {
        positionVectors[i] = unif(*generator);
    }
    positionVectorsParticlePbest = positionVectors;
}

void Particle::setStartSpeed() {
    std::uniform_real_distribution<double> unif(
            (config->lowerLimitPositionVector - config->upperLimitPositionVector) / (vectorDim * vectorDim),
            (config->upperLimitPositionVector - config->lowerLimitPositionVector) / (vectorDim * vectorDim)
    );
    for (int i = 0; i < vectorDim; i++) {
        speedVectors[i] = unif(*generator);
    }
}

#ifdef OPEN_MP_SWARM
void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2, int i, std::default_random_engine* gen)
{
    std::uniform_real_distribution<double> unif(0.0,1.0);
    double m=sqrt(vectorDim);
        double rand_1 = unif(*gen)/m;
        double rand_2 = unif(*gen)/m;
        double tempSpeedValue =
                w * speedVectors[i] + speedConstant1 * rand_1 * (positionVectorsParticlePbest[i] - positionVectors[i]) +
                speedConstant2 + rand_2 * (swarm->GbestVector[0].positionVectorsParticlePbest[i] - positionVectors[i]);
      //  cout<<"ts: "<<tempSpeedValue<<"\n";
        tempSpeedVectors[i] = tempSpeedValue;
}
#else

void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2, int i) {
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    double m = sqrt(vectorDim);
    double rand_1 = unif(*generator) / m;
    double rand_2 = unif(*generator) / m;
    double tempSpeedValue =
            w * speedVectors[i] + speedConstant1 * rand_1 * (positionVectorsParticlePbest[i] - positionVectors[i]) +
            speedConstant2 + rand_2 * (swarm->GbestVector[0].positionVectorsParticlePbest[i] - positionVectors[i]);
    //  cout<<"ts: "<<tempSpeedValue<<"\n";
    tempSpeedVectors[i] = tempSpeedValue;
}
#endif

#ifdef OPEN_MP_SWARM
void Particle::computePosition(float w, float speedConstant1, float speedConstant2, std::default_random_engine* gen)
#else
void Particle::computePosition(float w, float speedConstant1, float speedConstant2)
#endif

{
    vector<double> newPositionVector;
    newPositionVector.resize(vectorDim, 0.0);

    for (int i = 0; i < vectorDim; i++) {
        do {
#ifdef OPEN_MP_SWARM
            computeSpeed(w, speedConstant1, speedConstant2, i, gen);
#else
            computeSpeed(w, speedConstant1, speedConstant2, i);
#endif
            newPositionVector[i] = positionVectors[i] + tempSpeedVectors[i];
        } while (!config->isXInRange(newPositionVector[i]));
    }

    speedVectors = tempSpeedVectors;
    positionVectors = newPositionVector;
}

void Particle::computeCostFunctionValue() {
    costFunctionValue = config->computeCostFunctionValue(positionVectors);
}

void Particle::computeParticlePbest() {
    if (costFunctionValue < costFunctionValuePbest) {
        costFunctionValuePbest = costFunctionValue;
        positionVectorsParticlePbest = positionVectors;
    }
}

double Particle::getCostFunctionValue() {
    return costFunctionValue;
}

double Particle::getCostFunctionValuePbest() {
    return costFunctionValuePbest;
}

vector<double> Particle::getPositionVector() {
    return positionVectors;
}
