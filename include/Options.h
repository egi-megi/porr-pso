#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H

#include "OptimizationExercisesConfig.h"
#include "StopCriterionConfig.h"

class Options
{
public:
    Options();
    virtual ~Options() = default;

    OptimizationExercisesConfig* optimizationExerciseConfig;
    StopCriterionConfig* stopCriterionConfig;
    double stopCriterionThreshold;
    int amountOfParticles;
    int dimension;
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H