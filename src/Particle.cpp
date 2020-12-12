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

Particle::Particle() {
    ready = false;
}

Particle::Particle(const int mVectorsDim, Swarm *s, OptimizationExercisesConfig *mconfig,
                   std::default_random_engine *gen)
{
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
    ready = true;
}

Particle::~Particle() {
}

void Particle::setStartPosition()
{
    std::uniform_real_distribution<double> unif(config->lowerLimitPositionVector, config->upperLimitPositionVector);
    for (int i = 0; i < vectorDim; i++)
    {
        positionVectors[i] = unif(*generator);
    }
    positionVectorsParticlePbest = positionVectors;
}

void Particle::setStartSpeed()
{
    std::uniform_real_distribution<double> unif(
        (config->lowerLimitPositionVector - config->upperLimitPositionVector) / (vectorDim * vectorDim),
        (config->upperLimitPositionVector - config->lowerLimitPositionVector) / (vectorDim * vectorDim));
    for (int i = 0; i < vectorDim; i++)
    {
        speedVectors[i] = unif(*generator);
    }
}

void Particle::computeSpeed(float w, float speedConstant1, float speedConstant2, std::default_random_engine *gen)
{
    std::uniform_real_distribution<double> unif(0.0, 1.0);

    double rand_1 = unif(*gen);
    double rand_2 = unif(*gen);

    std::vector<double> v_velocityProposition = PositionVectorOperator::add(
        PositionVectorOperator::mult(w, speedVectors),
        PositionVectorOperator::add(
            PositionVectorOperator::mult(
                speedConstant1 * rand_1,
                PositionVectorOperator::minus(positionVectorsParticlePbest, positionVectors)),
            PositionVectorOperator::mult(
                speedConstant2 * rand_2,
                PositionVectorOperator::minus(swarm->globalBestParticle.first.positionVectors, positionVectors))));
    
    double k = 1;
    std::vector<double> v_positionProposition = PositionVectorOperator::add(positionVectors, v_velocityProposition);
    for(int i = 0; i < vectorDim; i++) {
        char violation = 0;
        if(v_positionProposition[i] > config->upperLimitPositionVector)
            violation = 1;
        else if(v_positionProposition[i] < config->lowerLimitPositionVector)
            violation = -1;

        if(violation) {
        /* Compute coefficient k so as to make x_{i+1,j} = x{i,j} + k*v{i, j} fit in
        the box constraints. */
            double c1 = violation > 0 ? config->upperLimitPositionVector : config->lowerLimitPositionVector;
            double k_temp = (- positionVectors[i] + c1) / v_velocityProposition[i];
            if (k_temp < k) k = k_temp;
        }
    }

    tempSpeedVectors = PositionVectorOperator::mult(k, v_velocityProposition);
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

void Particle::computePosition(float w, float speedConstant1, float speedConstant2, std::default_random_engine *gen)
{
    vector<double> newPositionVector(vectorDim);

    computeSpeed(w, speedConstant1, speedConstant2, gen);
    newPositionVector = PositionVectorOperator::add(positionVectors, tempSpeedVectors);

    if(!config->isPositionInRange(newPositionVector))
        throw "Particle out of the box constraints!";

    speedVectors = tempSpeedVectors;
    positionVectors = newPositionVector;
}
#endif

void Particle::computeCostFunctionValue() {
    costFunctionValue = config->computeCostFunctionValue(positionVectors);
}

void Particle::computeParticlePbest()
{
    if (costFunctionValue < costFunctionValuePbest)
    {
        costFunctionValuePbest = costFunctionValue;
        positionVectorsParticlePbest = positionVectors;
    }
}

double Particle::getCostFunctionValue() const
{
    return costFunctionValue;
}

double Particle::getCostFunctionValuePbest()
{
    return costFunctionValuePbest;
}

vector<double> Particle::getPositionVector()
{
    return positionVectors;
}

bool Particle::isReady() const {
    return ready;
}
