//
// Created by Agnieszka Jurkiewicz on 01/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_STOPCRITERIONCONFIG_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_STOPCRITERIONCONFIG_H
#include <vector>
#include <istream>

class StopCriterionConfig {
public:
    virtual double computeCostFunctionValue(std::vector<double> positionVector)=0;
    virtual bool isPositionOK(std::vector<double> positionVector)=0;
    virtual bool isXInRange(double position);
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_STOPCRITERIONCONFIG_H
