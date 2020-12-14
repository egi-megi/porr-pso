#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_STOPCRITERIONCONFIG_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_STOPCRITERIONCONFIG_H

#include "Particle.h"

#include <vector>
#include <istream>

class StopCriterionConfig
{
public:
    virtual ~StopCriterionConfig() = default;

    virtual bool computeStopCriterion(float criterionStopValue, const std::pair<Particle,
        Particle> &globalBestParticle) = 0;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_STOPCRITERIONCONFIG_H
