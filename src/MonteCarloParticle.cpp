//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#include "../include/MonteCarloParticle.h"
#include <iostream>
#include <math.h>
#include <random>
//#include <omp.h>

using namespace std;

MonteCarloParticle::MonteCarloParticle(){

}

MonteCarloParticle::MonteCarloParticle(const int mVectorsDim, OptimizationExercisesConfig *mconfig,
                   std::default_random_engine* gen) {
    vectorDim = mVectorsDim;
    generatorMC = gen;
    positionVectorsMC.resize(mVectorsDim, 0.0);
    config = mconfig;
    setStartPositionMC();
    costFunctionValueMC=config->computeCostFunctionValue(positionVectorsMC);
    costFunctionValueMinMC = costFunctionValueMC;
}

MonteCarloParticle::~MonteCarloParticle() {
}


void MonteCarloParticle::setStartPositionMC() {
    std::uniform_real_distribution<double> unif(config->lowerLimitPositionVector, config->upperLimitPositionVector);
    for (int i = 0; i < vectorDim; i++) {
        positionVectorsMC[i] = unif(*generatorMC);
    }
    positionVectorsMinMC = positionVectorsMC;
}



void MonteCarloParticle::computePositionMC(float sigma, float tVariable)
{
    vector<double> tempPositionVector;
    tempPositionVector.resize(vectorDim, 0.0);
    std::normal_distribution<double> normal(-1.0, 1.0);
    for (int i = 0; i < vectorDim; i++) {
        do {
            double rand = normal(*generatorMC);
            tempPositionVector[i] = positionVectorsMC[i] + sigma * rand;
        } while (!config->isXInRange(tempPositionVector[i]));
    }
    double costFunctionValueTempMC = config->computeCostFunctionValue(positionVectorsMC);
    computeParticleMinValuesMC(costFunctionValueTempMC, tempPositionVector, tVariable);
}

void MonteCarloParticle::computeParticleMinValuesMC(double costFunctionValueTempMC, vector<double> tempPositionVector, float tVariable) {
    if (costFunctionValueTempMC < costFunctionValueMC) {
        costFunctionValueMC = costFunctionValueTempMC;
        positionVectorsMC = tempPositionVector;
        if (costFunctionValueTempMC < costFunctionValueMinMC) {
            costFunctionValueMinMC = costFunctionValueTempMC;
            positionVectorsMinMC = tempPositionVector;
        }
    } else {
        float zRand;
        double zCheck;
        std::uniform_real_distribution<double> unif(0.0,1.0);
        zRand = unif(*generatorMC);
        zCheck = exp(-((costFunctionValueTempMC - costFunctionValueMC)/tVariable));
        if (zRand < zCheck) {
            costFunctionValueMC = costFunctionValueTempMC;
            positionVectorsMC = tempPositionVector;
        }
    }

}

double MonteCarloParticle::getCostFunctionValueMinMC()
{
    return costFunctionValueMinMC;
}
