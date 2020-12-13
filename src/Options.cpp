#include "../include/Options.h"

Options::Options()
{
    optimizationExerciseConfig = nullptr;
    stopCriterionConfig = nullptr;
    stopCriterionThreshold  = 0.1;
    amountOfParticles = 10;
    dimension = 3;

    verbose = true;
    timing = true;
}