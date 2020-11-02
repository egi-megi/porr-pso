//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#include <iostream>
#include <vector>
#include <functional>
#include "OptimizationExercisesConfig.h"
#include <random>
using namespace std;

class Swarm;

class Particle
{
public:
    Particle();
    Particle(int vectorDim, Swarm* s, OptimizationExercisesConfig* config );
    virtual ~Particle();

    void setStartPosition();
    void setStartSpeed();
    void computePosition(float w, float speedConstant1, float speedConstant2);
    void computeSpeed(float w, float speedConstant1, float speedConstant2, int i);
    void computeCostFunctionValue();
    void computeParticlePbest();
    double getParticlePbest();
    double getCostFunctionValuePbest();
    vector <double > getPositionVector();

    double costFunctionValuePbest;
    vector <double > positionVectorsParticlePbest;

protected:

private:
    int vectorDim;
    vector <double > positionVectors;
    vector <double > speedVectors;
    vector <double > tempSpeedVectors;
    double costFunctionValue;
    double particlePbest;
    Swarm* swarm;
    OptimizationExercisesConfig* config;
    //double speedVectors[];
    //vector <double > speedVectorsParticlePbest;
    static std::default_random_engine generator;
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
