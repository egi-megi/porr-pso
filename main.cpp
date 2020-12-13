#include <iostream>

#include "include/SwarmParticle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include "include/MonteCarloParticle.h"
#include "include/MonteCarlo.h"
#include "include/Options.h"

int main()
{
    Options* options = new Options();
    options->optimizationExerciseConfig = new ConfigEx1();
    options->stopCriterionConfig = new ConfigStopCriterionAcademic();

    Swarm s1a(options);
    SwarmParticle s1a_best = s1a.findTheBestParticle(0.8, .1, .2);

    // Swarm s1a(10, 3, new ConfigEx1());
    // SwarmParticle s1a_best = s1a.findTheBestParticle(0.1, 0.8, .1, .2, new ConfigStopCriterionAcademic());
    
    printf("Best particle f(s1a_best) = %lf\n", s1a_best.getCostFunctionValue());

    MonteCarlo mc1a(options);
    MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(1, 8);

    // MonteCarlo mc1a(10, 3, new ConfigEx1());
    // MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(0.1, 1, 8, new ConfigStopCriterionAcademic());

    printf("Best particle f(mc1a_best) = %lf\n", mc1a_best.getCostFunctionValue());

    return 0;
}