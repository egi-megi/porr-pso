//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#include "../include/ConfigEx1.h"
#include <math.h>

double ConfigEx1::computeCostFunctionValue(std::vector<double> positionVector)
{
    double suma = 0;
    double product = 1;
    for (int i = 0; i <positionVector.size(); i++) {
        suma = suma + pow(positionVector[i], 2);
        product = product * cos(positionVector[i]/( i+ 1));
    }
    return 1/40 * suma + 1 - product;
}

bool ConfigEx1::isPositionOK(std::vector<double> positionVector){
    return true;
}