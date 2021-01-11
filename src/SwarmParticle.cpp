#include "../include/SwarmParticle.h"

#include "../include/Swarm.h"
#include "../include/PositionVectorOperator.h"
#include "../include/Options.h"

#include <iostream>
#include <math.h>
#include <random>

using namespace std;

SwarmParticle::SwarmParticle(Options* mOptions, Swarm *s,
    std::default_random_engine *gen)
{
    options = mOptions;

    vectorDim = options->dimension;
    speedVectors.resize(vectorDim, 0.0);
    tempSpeedVectors.resize(vectorDim, 0.0);
    positionVectors.resize(vectorDim, 0.0);

    config = options->optimizationExerciseConfig;

    setStartPosition(*gen);
    positionVectorsParticlePbest = positionVectors;
    setStartSpeed(*gen);

    computeCostFunctionValue();
    costFunctionValuePbest = costFunctionValue;
    cout<<"COst particle :"<<costFunctionValue<<'\n';
    swarm = s;

    communication = options->communication;

    ready = true;
}

std::vector<double> SwarmParticle::getSpeedVector() 
{
    return speedVectors;
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
                PositionVectorOperator::minus(getBestVisibleParticlePosition(),
                    positionVectors))));

    std::vector<double> v_positionProposition = PositionVectorOperator::add(positionVectors,
        v_velocityProposition);
    tempSpeedVectors = PositionVectorOperator::mult(getCoefficientForBoundedPosition(v_positionProposition,
        v_velocityProposition), v_velocityProposition);
}

vector<double>& SwarmParticle::getBestVisibleParticlePosition()
{
    if(communication == Options::CommunicationType::GLOBAL_BEST)
        return swarm->globalBestParticle.first.positionVectors;
    else if(communication == Options::CommunicationType::LOCAL_BEST)
        return v_localBestParticleVisiblePosition;
    else
        throw "I don't know the communication type!";
}

void SwarmParticle::setLocalBestParticleVisiblePosition(const vector<double> &particlePosition)
{
    v_localBestParticleVisiblePosition = particlePosition;
}

void SwarmParticle::computePosition(float w, float speedConstant1, float speedConstant2,
    std::default_random_engine *gen)
{
    vector<double> newPositionVector(vectorDim);

    computeSpeed(w, speedConstant1, speedConstant2, gen);
    newPositionVector = PositionVectorOperator::add(positionVectors, tempSpeedVectors);

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