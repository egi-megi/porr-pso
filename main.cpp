#include <iostream>
#include "include/Particle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include <math.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main() {
    
    //particles log only for n=2
    //isLogAll =true - log all data for all particles

    int dim = 2;
    Logger log_temp;
    std::string date = log_temp.currentDateTime();

    std::string bestParticlesLogFileName = "../logs/log_" + date + ".txt";
    std::string allParticlesLogFileName = "../logs/particlesLog_" + date + ".txt";

    // Logger* log = new Logger("../log.txt", "../particlesLog.txt", dim, true);
    Logger* log = new Logger(bestParticlesLogFileName, allParticlesLogFileName, dim, true);
    Logger::ParamStruct params (25, dim, 0.001f, 0.8f, 0.1f, 0.2f, 1000, log);


    srand (time(NULL));
    for (int i=0 ;i<1; i++) {
    Swarm s1a(params.amountOfParticles, params.vectorDim, log, new ConfigEx1());    
    Particle theBestParticle1a = s1a.findTheBestParticle(params.stopCriterion, params.weight, params.speedConst1, params.speedConst2, log, new ConfigStopCriterionAcademic());
    log->logAndClose();

    //Swarm s1n(100, 10, new ConfigEx1());
    //Particle theBestParticle1n = s1n.findTheBestPartiScle(0.1, 1.0, 0.1, 0.1, new ConfigStopCriterionNormal());

    //Swarm s2a(1000, 40, new ConfigEx2());
    //Particle theBestParticle2a = s2a.findTheBestParticle(0.5, 0.00001, 0.00001, 0.00001, new ConfigStopCriterionAcademic());

    //Swarm s2n(100, 4, new ConfigEx2());
    //Particle theBestParticle2n = s2n.findTheBestParticle(0.5, 0.1, 0.1, 0.1, new ConfigStopCriterionNormal());

    std::cout << "Cost function for Gbest particle for exercise 1 for academic criterion of stop: " << theBestParticle1a.costFunctionValuePbest << std::endl;
    //std::cout << "Cost function for Gbest particle for exercise 1 for normal criterion of stop: " << theBestParticle1n.costFunctionValuePbest << std::endl;
    //std::cout << "Cost function for Gbest particle for exercise 2 for academic criterion of stop: "<< theBestParticle2a.costFunctionValuePbest << std::endl;
    //std::cout << "Cost function for Gbest particle for exercise 2 for normal criterion of stop: " << theBestParticle2n.costFunctionValuePbest << std::endl;
}
    return 0;
}
  