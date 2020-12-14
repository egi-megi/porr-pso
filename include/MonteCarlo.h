#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H

#include <vector>

#include "MonteCarloParticle.h"
#include "StopCriterionConfig.h"
#include "Options.h"
#include "Logger.h"

class MonteCarlo
{
public:
    MonteCarlo() = default;
    MonteCarlo(Options *mOptions, Logger *log);
    virtual ~MonteCarlo() = default;

    void makeMonteCarlo();
    void computeGlobalBest(MonteCarloParticle *particle);
    MonteCarloParticle findTheBestParticle(float criterionStopValue, float sigma, float T,
        StopCriterionConfig *configStop);
    MonteCarloParticle findTheBestParticle(float sigma, float T);
    std::pair<MonteCarloParticle, MonteCarloParticle> globalBestParticle;
    
private:
    void monteCarloLogger(const int& iteration, const double& cost);
    int amountOfParticles;
    int vectorDim;
    std::vector<MonteCarloParticle> v_particles;
    Options *options;
    Logger *log;
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H