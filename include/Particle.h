//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H

#include <iostream>
#include <vector>
#include <functional>
#include <random>

#include "ParticleBase.h"
#include "OptimizationExercisesConfig.h"

using namespace std;

class Swarm;

class Particle : public ParticleBase
{
public:
    Particle();
    Particle(int vectorDim, Swarm *s, OptimizationExercisesConfig *config,
             std::default_random_engine *generator);
    virtual ~Particle() = default;

    void setStartSpeed();
    void computePosition(float w, float speedConstant1, float speedConstant2,
                         std::default_random_engine *gen);
    void computeSpeed(float w, float speedConstant1, float speedConstant2,
                      std::default_random_engine *gen);
    void computeParticlePbest();

    double getCostFunctionValuePbest();

    double costFunctionValuePbest;
    vector<double> positionVectorsParticlePbest;

    bool isReady() const;

protected:
private:
    vector<double> speedVectors;
    vector<double> tempSpeedVectors;
    Swarm *swarm;
    bool ready;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
