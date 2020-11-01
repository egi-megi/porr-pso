//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX1_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX1_H


#include "OptimizationConfig.h"

class ConfigEx1 : public OptimizationConfig{
public:
    double computeCostFunctionValue(std::vector<double> positionVector);
    bool isPositionOK(std::vector<double> positionVector);
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX1_H
