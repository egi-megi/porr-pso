//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H

#include <iostream>
#include <vector>
#include <functional>
#include <random>

#include "OptimizationExercisesConfig.h"
#include "PositionVectorOperator.h"

using namespace std;

class Swarm;

class Particle
{
public:
    Particle();
    Particle(int vectorDim, Swarm *s, OptimizationExercisesConfig *config,
             std::default_random_engine *generator);
    virtual ~Particle() = default;

    void setStartPosition();
    void setStartSpeed();
    void computePosition(float w, float speedConstant1, float speedConstant2,
                         std::default_random_engine *gen);
    void computeSpeed(float w, float speedConstant1, float speedConstant2,
                      std::default_random_engine *gen);
    void computeCostFunctionValue();
    void computeParticlePbest();
    double getCostFunctionValue() const;

    double getCostFunctionValuePbest();
    vector<double> getPositionVector();

    double costFunctionValuePbest;
    vector<double> positionVectorsParticlePbest;

    bool isReady() const;

protected:
private:
    double getCoefficientForBoundedPosition(vector<double> &v_positionProposition,
        vector<double> &v_positionDelta);

    int vectorDim;
    vector<double> positionVectors;
    vector<double> speedVectors;
    vector<double> tempSpeedVectors;
    double costFunctionValue;
    Swarm *swarm;
    OptimizationExercisesConfig *config;
    std::default_random_engine *generator;
    bool ready;

    friend class PositionVectorOperator;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
