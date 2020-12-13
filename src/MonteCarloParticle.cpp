#include <random>
#include <vector>
#include <math.h>

#include "../include/MonteCarloParticle.h"
#include "../include/OptimizationExercisesConfig.h"
#include "../include/PositionVectorOperator.h"

MonteCarloParticle::MonteCarloParticle(const int mVectorDim,
    OptimizationExercisesConfig *mconfig, std::default_random_engine &gen)
{
    vectorDim = mVectorDim;
    positionVectors.resize(mVectorDim, 0);
    config = mconfig;
    setStartPosition(gen);
    computeCostFunctionValue();
    ready = true;
}

void MonteCarloParticle::computePosition(float sigma, float T, std::default_random_engine &gen)
{
    std::normal_distribution<double> normal(0, 1);
    std::vector<double> v_positionDelta(vectorDim);
    for(int i = 0; i < vectorDim; i++)
        v_positionDelta[i] = sigma*normal(gen);
    
    std::vector<double> v_positionProposition = PositionVectorOperator::add(
        positionVectors,
        v_positionDelta
    );

    // Make the proposition fit in box constraints
    v_positionProposition = PositionVectorOperator::add(
        v_positionProposition,
        PositionVectorOperator::mult(
            getCoefficientForBoundedPosition(v_positionProposition, v_positionDelta),
            v_positionDelta
        )
    );

    double costFunctionValueProposition = getCostFunctionValue(v_positionProposition);
    if(costFunctionValueProposition < costFunctionValue)
    {
        costFunctionValue = costFunctionValueProposition;
        positionVectors = v_positionProposition;
    }
    else
    {
        double threshold = std::exp(-(costFunctionValueProposition - costFunctionValue) / T);
        std::uniform_real_distribution<double> uniform(0, 1);
        if(uniform(gen) < threshold)
        {
            costFunctionValue = costFunctionValueProposition;
            positionVectors = v_positionProposition;
        }
    }
}