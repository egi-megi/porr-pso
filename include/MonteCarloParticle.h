//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H

#include <iostream>
#include <vector>
#include <functional>
#include "OptimizationExercisesConfig.h"
#include <random>
//#include <omp.h>
using namespace std;

class MonteCarloParticle {
public:
    MonteCarloParticle();

    MonteCarloParticle(int vectorDim, OptimizationExercisesConfig *config, std::default_random_engine *generator);

    virtual ~MonteCarloParticle();

    void setStartPositionMC();

    void computePositionMC(float sigma, float T);

    void computeParticleMinValuesMC(double costFunctionValueTempMC, vector<double> tempPositionVector, float tVariable);

    double getCostFunctionValueMinMC();

private:
    int vectorDim;
    vector<double> positionVectorsMC;
    vector<double> positionVectorsMinMC;
    double costFunctionValueMC;
    double costFunctionValueMinMC;
    OptimizationExercisesConfig *config;
    std::default_random_engine *generatorMC;
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H
