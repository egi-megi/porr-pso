#include <random>
#include <vector>

#include "../include/ParticleBase.h"

void ParticleBase::setStartPosition()
{
    std::uniform_real_distribution<double> unif(config->lowerLimitPositionVector,
        config->upperLimitPositionVector);
    for (int i = 0; i < vectorDim; i++)
    {
        positionVectors[i] = unif(*generator);
    }
}

void ParticleBase::computeCostFunctionValue()
{
    costFunctionValue = config->computeCostFunctionValue(positionVectors);
}

double ParticleBase::getCostFunctionValue() const
{
    return costFunctionValue;
}

std::vector<double> ParticleBase::getPositionVector()
{
    return positionVectors;
}

double ParticleBase::getCoefficientForBoundedPosition(std::vector<double> &v_positionProposition,
    std::vector<double> &v_positionDelta)
{
    double k = 1;
    for (int i = 0; i < vectorDim; i++)
    {
        char violation = 0;
        if (v_positionProposition[i] > config->upperLimitPositionVector)
            violation = 1;
        else if (v_positionProposition[i] < config->lowerLimitPositionVector)
            violation = -1;

        if (violation)
        {
            /* Compute coefficient k so as to make x_{i+1,j} = x{i,j} + k*v{i, j} fit in
            the box constraints. */
            double c1 = violation > 0 ? config->upperLimitPositionVector : config->lowerLimitPositionVector;
            double k_temp = (-positionVectors[i] + c1) / v_positionDelta[i];
            if (k_temp < k)
                k = k_temp;
        }
    }
    return k;
}