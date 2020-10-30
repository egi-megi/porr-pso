//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H

#include "Particle.h"
#include <iostream>
#include <vector>

using namespace std;

class Swarm
{
public:
    Swarm(int mAmountOfParticles, int mVectorDim, std::function<double(vector<double>)> mfunctionToOptimize );
    virtual ~Swarm();

    void makeSwarm(int amountOfParticles, int vectorDim,std::function<double(vector<double>)> mfunctionToOptimize );
    void computeGbest(Particle *particle);
    Particle findTheBestParticle(float academicCondition, float w, float speedConstant1, float speedConstant2);

    Particle *Gbest;

protected:


private:

    int amountOfParticles;
    int vectorDim;
    vector <Particle> swarm;
    float epsilon;


};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
