//
// Created by Agnieszka Jurkiewicz on 02/11/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONNORMAL_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONNORMAL_H
#include "StopCriterionConfig.h"
#include "Particle.h"

class ConfigStopCriterionNormal : public StopCriterionConfig {
public:
    bool computeStopCriterion(float criterionStopValue, const std::pair<Particle, Particle>& globalBestParticle);
};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONNORMAL_H
