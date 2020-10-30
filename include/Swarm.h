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
    Swarm(int mAmountOfParticles, int mVectorDim, int exerciseNumber);
    virtual ~Swarm();

    void makeSwarm(int amountOfParticles, int vectorDim);
    void computeGbest(Particle *particle);
    int getExercisseNumber();

    Particle *Gbest;

protected:


private:

    int amountOfParticles;
    int vectorDim;
    vector <Particle> swarm;
    int exerciseNumber;

};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
