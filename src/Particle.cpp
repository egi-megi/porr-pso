#include "../include/Particle.h"

#include <random>
#include <vector>

void Particle::setStartPosition(std::default_random_engine &gen)
{
    std::uniform_real_distribution<double> unif(options->getLowerBoundBoxInitialization(),
        options->getUpperBoundBoxInitialization());
    for (int i = 0; i < vectorDim; i++)
    {
        positionVectors[i] = unif(gen);
    }
}

void Particle::computeCostFunctionValue()
{
    costFunctionValue = config->computeCostFunctionValue(positionVectors);
}

double Particle::getCostFunctionValue() const
{
    return costFunctionValue;
}

double Particle::getCostFunctionValue(std::vector<double> &v_position) const
{
    return config->computeCostFunctionValue(v_position);
}

std::vector<double> Particle::getPositionVector()
{
    return positionVectors;
}

double Particle::getCoefficientForBoundedPosition(std::vector<double> &v_positionProposition,
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

bool Particle::isReady() const
{
    return ready;
}
void Particle::setId(const int& id) 
{
    particleId = id;
}

int Particle::getParticleId() 
{
    return particleId;
}
