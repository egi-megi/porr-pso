#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONNORMAL_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONNORMAL_H

#include "StopCriterionConfig.h"
#include "Particle.h"

class ConfigStopCriterionNormal : public StopCriterionConfig
{
public:
    ConfigStopCriterionNormal(int mThreshold);
    bool computeStopCriterion(float criterionStopValue, const std::pair<Particle,
        Particle> &globalBestParticle);
    void reset();

private:
    int checksFallenBelowStopValue;
    int threshold;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_CONFIGSTOPCRITERIONNORMAL_H
