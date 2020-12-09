//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX2_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX2_H

#include <iostream>
#include <vector>
#include "OptimizationExercisesConfig.h"

class ConfigEx2 : public OptimizationExercisesConfig{

public:
    ConfigEx2();
    virtual ~ConfigEx2();
    double computeCostFunctionValue(std::vector<double> positionVector);
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX2_H
