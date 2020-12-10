//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#include "../include/MonteCarloParticlesSet.h"
#include <random>

#ifdef OPEN_MP
#include <omp.h>
#endif

std::default_random_engine MonteCarloParticlesSet::generatorMC;

MonteCarloParticlesSet::MonteCarloParticlesSet(const int mVectorsDim, int mAmountOfParticles, int mNumberOfDraws, OptimizationExercisesConfig* config, float sigma, float tVariable)
{
    amountOfParticles = mAmountOfParticles;
    numberOfSteps = mNumberOfDraws;

    computeTheBestParticleMC(sigma, tVariable, config, mVectorsDim);
}

MonteCarloParticlesSet::~MonteCarloParticlesSet()
{
}

bool costFunSort(MonteCarloParticle p1, MonteCarloParticle p2) {
    return (p1.getCostFunctionValueMinMC() < p2.getCostFunctionValueMinMC());
}

MonteCarloParticle MonteCarloParticlesSet::computeTheBestParticleMC(float sigma, float tVariable, OptimizationExercisesConfig* config, const int mVectorsDim)
{
#ifdef OPEN_MP
    int i;
	int n = amountOfParticles;
	int s = monteCarloParticlesVector.size();
    std::vector<std::default_random_engine*> rand_engines(omp_get_num_procs());
	for (int j = 0; j < omp_get_num_procs(); j++) {
		rand_engines[j] = new std::default_random_engine();
		rand_engines[j]->seed(rand());
		cout << "seed " << j << " " << (*rand_engines[j])() << "\n";
	}
	monteCarloParticlesVector.resize(n);
    # pragma omp parallel for private(i) shared(n, monteCarloParticlesVector, rand_engines)
    for (i = 0; i < n; i++) {
        MonteCarloParticle particleMC (mVectorsDim, config, (rand_engines[omp_get_thread_num()]));
        for (int j = 0; j < numberOfSteps; j++) {
            particleMC.computePositionMC(sigma, tVariable);
           // if (j%10000==0) {
           //     std::cout<<"step "<<j << " partile "<<i<<std::endl;
           // }
        }
        if (i%10==0) {
            std::cout<<"processed particle "<<i<<std::endl;
        }
        monteCarloParticlesVector[s + i] = particleMC;
    }
#else
    for (int i = 0; i < amountOfParticles; i++) {
        MonteCarloParticle particleMC (mVectorsDim, config, &generatorMC);
        for (int j = 0; j < numberOfSteps; j++) {
            particleMC.computePositionMC(sigma, tVariable);
           // if (j%10000==0) {
           //     std::cout<<"step "<<j << " partile "<<i<<std::endl;
           // }
        }
        if (i%10==0) {
            std::cout<<"processed particle "<<i<<std::endl;
        }
        monteCarloParticlesVector.push_back(particleMC);
    }
#endif
    std::sort(monteCarloParticlesVector.begin(), monteCarloParticlesVector.end(), costFunSort);
    return monteCarloParticlesVector[0];
}