//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONACADEMIC_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONACADEMIC_H

#include "StopCriterionConfig.h"
#include "Particle.h"

class ConfigStopCriterionAcademic : public StopCriterionConfig {
public:
    bool computeStopCriterion(float criterionStopValue, vector <Particle>* GbestVector);
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONACADEMIC_H
