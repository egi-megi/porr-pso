#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARMPARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARMPARTICLE_H

#include "Particle.h"
#include "OptimizationExercisesConfig.h"
#include "Options.h"

#include <iostream>
#include <vector>
#include <functional>
#include <random>

using namespace std;

class Swarm;

class SwarmParticle : public Particle
{
public:
    SwarmParticle() = default;
    SwarmParticle(Options *mOptions, Swarm *s, std::default_random_engine *gen);
    SwarmParticle(Options *mOptions, Swarm *s, std::default_random_engine *gen, std::vector<double> positionVector);
    
    virtual ~SwarmParticle() = default;

    std::vector<double> getSpeedVector();
    void setStartSpeed(std::default_random_engine &gen);
    void computePosition(float w, float speedConstant1, float speedConstant2,
        std::default_random_engine *gen);
    void computeSpeed(float w, float speedConstant1, float speedConstant2,
        std::default_random_engine *gen);
    void computeParticlePbest();

    double getCostFunctionValuePbest();

    void setLocalBestParticleVisiblePosition(const vector<double> &particlePosition);

    double costFunctionValuePbest;
    vector<double> positionVectorsParticlePbest;

private:
    vector<double>& getBestVisibleParticlePosition();

    vector<double> v_localBestParticleVisiblePosition;
    vector<double> speedVectors;
    vector<double> tempSpeedVectors;
    Swarm *swarm;

    Options::CommunicationType communication;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARMPARTICLE_H