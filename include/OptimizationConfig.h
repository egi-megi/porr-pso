//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIMIZATIONCONFIG_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIMIZATIONCONFIG_H
#include <vector>
class OptimizationConfig {
public:
    virtual double computeCostFunctionValue(std::vector<double> positionVector)=0;
    virtual bool isPositionOK(std::vector<double> positionVector)=0;
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIMIZATIONCONFIG_H
