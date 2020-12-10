//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
#include <iostream>
#include <vector>
#include <functional>
#include "OptimizationExercisesConfig.h"
#include "MonteCarloParticle.h"
#include <random>
//#include <omp.h>
using namespace std;


class MonteCarloParticlesSet {
public:
    MonteCarloParticlesSet(const int mVectorsDim, int mAmountOfParticles, int mNumberOfDraws, OptimizationExercisesConfig* config, float sigma, float tVariable);
    virtual ~MonteCarloParticlesSet();

    MonteCarloParticle computeTheBestParticleMC(float sigma, float tVariable, OptimizationExercisesConfig* config, const int mVectorsDim);

    vector<MonteCarloParticle> monteCarloParticlesVector;
private:
    int amountOfParticles;
    int numberOfSteps;
    static std::default_random_engine generatorMC;

};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
