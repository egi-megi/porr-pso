#include "../include/MonteCarloParticle.h"

#include "../include/OptimizationExercisesConfig.h"
#include "../include/PositionVectorOperator.h"
#include "../include/Options.h"

#include <random>
#include <vector>
#include <math.h>

MonteCarloParticle::MonteCarloParticle(Options* mOptions, std::default_random_engine &gen)
{
    options = mOptions;

    vectorDim = options->dimension;
    positionVectors.resize(vectorDim, 0);

    config = options->optimizationExerciseConfig;

    setStartPosition(gen);
    computeCostFunctionValue();
    
    ready = true;
}

MonteCarloParticle::MonteCarloParticle(Options *mOptions, std::default_random_engine &gen, std::vector<double> _positionVector) 
{
    options = mOptions;

    vectorDim = options->dimension;
    positionVectors.resize(vectorDim, 0);

    config = options->optimizationExerciseConfig;

    positionVectors = _positionVector; // load positions from file
    computeCostFunctionValue();
    
    ready = true;
}

void MonteCarloParticle::computePosition(float sigma, float T, std::default_random_engine &gen)
{
    std::uniform_real_distribution<double> uniform(-1, 1);
    std::vector<double> v_positionDelta(vectorDim);
    for(int i = 0; i < vectorDim; i++)
        v_positionDelta[i] = sigma*uniform(gen);
    
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
        std::uniform_real_distribution<double> uniform(0, 1);
        double threshold = std::exp(-(costFunctionValueProposition - costFunctionValue) / T);
        if(uniform(gen) < threshold)
        {
            costFunctionValue = costFunctionValueProposition;
            positionVectors = v_positionProposition;
        }
    }
}