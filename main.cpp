#include <iostream>
#include "include/Particle.h"
#include "include/Swarm.h"
#include <math.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

double computeCostFunctionValueEx1(vector<double> positionVector)
{
    double suma = 0;
    double product = 1;
    for (int i = 0; i <positionVector.size(); i++) {
        suma = suma + pow(positionVector[i], 2);
        product = product * cos(positionVector[i]/( i+ 1));
    }
    return 1/40 * suma + 1 - product;
}

double computeCostFunctionValueEx2(vector<double> positionVector)
{
    double costFunctionValue = 0.0;
    for (int i = 1; i < positionVector.size(); i++) {
        costFunctionValue = costFunctionValue + (100 * pow((positionVector[i + 1] - pow(positionVector[i], 2)), 2) + (1 - pow(positionVector[i], 2)));
    }
    return costFunctionValue;
}

int main() {

    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;

    Swarm s(2, 2, computeCostFunctionValueEx2, 2);
    Particle theBestParticle = s.findTheBestParticle(0.2, 1.0, 0.1, 0.1);

    std::cout << "Po obliczeniu f. kosztu" << std::endl;
    std::cout << theBestParticle.costFunctionValuePbest << std::endl;

    return 0;
}
