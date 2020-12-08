//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
#include <iostream>
#include <vector>
#include <functional>
#include "OptimizationExercisesConfig.h"
#include <random>
//#include <omp.h>
using namespace std;


class MonteCarlo {
public:
    MonteCarlo();
    virtual ~MonteCarlo();

private:
    long amountOfParticles;
    long amountOfRandom;


};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLO_H
