#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H

#include <vector>

#include "MonteCarloParticle.h"
#include "StopCriterionConfig.h"

class MonteCarlo
{
public:
    MonteCarlo() = default;
    MonteCarlo(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig *config);
    virtual ~MonteCarlo() = default;

    void makeMonteCarlo(OptimizationExercisesConfig &config);
    void computeGlobalBest(MonteCarloParticle *particle);
    MonteCarloParticle findTheBestParticle(float criterionStopValue, float sigma, float T,
        StopCriterionConfig *configStop);
    std::pair<MonteCarloParticle, MonteCarloParticle> globalBestParticle;

private:
    int amountOfParticles;
    int vectorDim;
    std::vector<MonteCarloParticle> v_particles;
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H