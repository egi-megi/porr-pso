//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H

#include <iostream>
#include <vector>
#include <functional>
#include <random>

#include "Particle.h"
#include "OptimizationExercisesConfig.h"

using namespace std;

class Swarm;

class SwarmParticle : public Particle
{
public:
    SwarmParticle() = default;
    SwarmParticle(int vectorDim, Swarm *s, OptimizationExercisesConfig *config,
             std::default_random_engine *generator);
    virtual ~SwarmParticle() = default;

    void setStartSpeed(std::default_random_engine &gen);
    void computePosition(float w, float speedConstant1, float speedConstant2,
                         std::default_random_engine *gen);
    void computeSpeed(float w, float speedConstant1, float speedConstant2,
                      std::default_random_engine *gen);
    void computeParticlePbest();

    double getCostFunctionValuePbest();

    double costFunctionValuePbest;
    vector<double> positionVectorsParticlePbest;

private:
    vector<double> speedVectors;
    vector<double> tempSpeedVectors;
    Swarm *swarm;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
