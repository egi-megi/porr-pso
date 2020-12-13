//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#include <iostream>
#include <math.h>
#include <random>

#include "../include/SwarmParticle.h"
#include "../include/Swarm.h"
#include "../include/PositionVectorOperator.h"

using namespace std;

SwarmParticle::SwarmParticle()
{
    ready = false;
}

SwarmParticle::SwarmParticle(const int mVectorsDim, Swarm *s, OptimizationExercisesConfig *mconfig,
                   std::default_random_engine *gen)
{
    vectorDim = mVectorsDim;
    speedVectors.resize(mVectorsDim, 0.0);
    tempSpeedVectors.resize(mVectorsDim, 0.0);
    positionVectors.resize(mVectorsDim, 0.0);
    config = mconfig;
    setStartPosition(*gen);
    positionVectorsParticlePbest = positionVectors;
    setStartSpeed(*gen);
    computeCostFunctionValue();
    swarm = s;
    costFunctionValuePbest = costFunctionValue;
    ready = true;
}

void SwarmParticle::setStartSpeed(std::default_random_engine &gen)
{
    std::uniform_real_distribution<double> unif(
        (config->lowerLimitPositionVector - config->upperLimitPositionVector) / (vectorDim * vectorDim),
        (config->upperLimitPositionVector - config->lowerLimitPositionVector) / (vectorDim * vectorDim));
    for (int i = 0; i < vectorDim; i++)
    {
        speedVectors[i] = unif(gen);
    }
}

void SwarmParticle::computeSpeed(float w, float speedConstant1, float speedConstant2,
    std::default_random_engine *gen)
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
                PositionVectorOperator::minus(swarm->globalBestParticle.first.positionVectors,
                    positionVectors))));

    std::vector<double> v_positionProposition = PositionVectorOperator::add(positionVectors,
        v_velocityProposition);
    tempSpeedVectors = PositionVectorOperator::mult(getCoefficientForBoundedPosition(v_positionProposition,
        v_velocityProposition), v_velocityProposition);
}

void SwarmParticle::computePosition(float w, float speedConstant1, float speedConstant2,
    std::default_random_engine *gen)
{
    vector<double> newPositionVector(vectorDim);

    computeSpeed(w, speedConstant1, speedConstant2, gen);
    newPositionVector = PositionVectorOperator::add(positionVectors, tempSpeedVectors);

    if (!config->isPositionInRange(newPositionVector))
        throw "Particle out of the box constraints!";

    speedVectors = tempSpeedVectors;
    positionVectors = newPositionVector;
}

void SwarmParticle::computeParticlePbest()
{
    if (costFunctionValue < costFunctionValuePbest)
    {
        costFunctionValuePbest = costFunctionValue;
        positionVectorsParticlePbest = positionVectors;
    }
}

double SwarmParticle::getCostFunctionValuePbest()
{
    return costFunctionValuePbest;
}