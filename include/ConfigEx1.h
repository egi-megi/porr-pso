//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX1_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX1_H

#include <vector>

#include "OptimizationExercisesConfig.h"

class ConfigEx1 : public OptimizationExercisesConfig{

public:
    ConfigEx1();
    virtual ~ConfigEx1();
    double computeCostFunctionValue(std::vector<double> positionVector);
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGEX1_H
