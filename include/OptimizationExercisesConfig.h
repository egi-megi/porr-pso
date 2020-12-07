//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIMIZATIONEXERCISESCONFIG_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIMIZATIONEXERCISESCONFIG_H
#include <vector>
#include <istream>

class OptimizationExercisesConfig {

public:
    OptimizationExercisesConfig();
    virtual ~OptimizationExercisesConfig();
    virtual double computeCostFunctionValue(std::vector<double> positionVector)=0;
    virtual bool isPositionOK(std::vector<double> positionVector)=0;
    virtual bool isXInRange(double position);
    double lowerLimitPositionVector;
    double upperLimitPositionVector;
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIMIZATIONEXERCISESCONFIG_H
