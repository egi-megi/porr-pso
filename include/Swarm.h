//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H

#include "Particle.h"
#include "ConfigStopCriterionAcademic.h"
#include "ConfigStopCriterionNormal.h"
#include "StopCriterionConfig.h"
#include <iostream>
#include <vector>

using namespace std;

class Swarm
{
public:
    Swarm(int mAmountOfParticles, int mVectorDim, OptimizationExercisesConfig* config);
    virtual ~Swarm();

    void makeSwarm(int amountOfParticles, int vectorDim, OptimizationExercisesConfig* config);
    void computeGbest(Particle *particle);
    Particle findTheBestParticle(float criterionStopValue, float w, float speedConstant1, float speedConstant2, StopCriterionConfig *configStop);

    Particle *Gbest;
    Particle *GbestOld;

protected:


private:

    int amountOfParticles;
    int vectorDim;
    vector <Particle> swarm;
    float criterionStopValue;


};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
