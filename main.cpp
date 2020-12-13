#include "include/SwarmParticle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include "include/MonteCarloParticle.h"
#include "include/MonteCarlo.h"
#include "include/Options.h"
#include "include/InputParser.h"

#include <iostream>

int main(int argc, char* argv[])
{
    Options* options = new Options();
    options->optimizationExerciseConfig = new ConfigEx1();
    options->stopCriterionConfig = new ConfigStopCriterionAcademic();

    InputParser::parse(options, argc, argv);

    Swarm s1a(options);
    SwarmParticle s1a_best = s1a.findTheBestParticle(0.8, .1, .2);
    
    printf("Best particle f(s1a_best) = %lf\n", s1a_best.getCostFunctionValue());

    // MonteCarlo mc1a(options);
    // MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(1, 8);

    // printf("Best particle f(mc1a_best) = %lf\n", mc1a_best.getCostFunctionValue());

    delete options->optimizationExerciseConfig;
    delete options->stopCriterionConfig;
    delete options;

    return 0;
}