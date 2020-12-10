#include <iostream>
#include "include/Particle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include "include/MonteCarloParticle.h"
#include "include/MonteCarloParticlesSet.h"
#include <math.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main() {

    srand (time(NULL));
    std::cout << "Początek obliczeń" << std::endl;
    for (int i=0 ;i<1; i++) {
        MonteCarloParticlesSet setMC1(20, 10000, 100, new ConfigEx1(), 0.01, 0.01);

        //MonteCarloParticlesSet setMC2(20, 10000, 100, new ConfigEx2(), 0.1, 0.9);

        //Swarm s1a(200000, 50, new ConfigEx1());
        //Particle theBestParticle1a = s1a.findTheBestParticle(0.1, 0.00001, 0.00001, 0.00001, new ConfigStopCriterionAcademic());


        //Swarm s1n(100, 10, new ConfigEx1());
        //Particle theBestParticle1n = s1n.findTheBestParticle(0.1, 1.0, 0.1, 0.1, new ConfigStopCriterionNormal());

        //Swarm s2a(1000, 40, new ConfigEx2());
        //Particle theBestParticle2a = s2a.findTheBestParticle(0.5, 0.00001, 0.00001, 0.00001, new ConfigStopCriterionAcademic());

        //Swarm s2n(100, 4, new ConfigEx2());
        //Particle theBestParticle2n = s2n.findTheBestParticle(0.5, 0.1, 0.1, 0.1, new ConfigStopCriterionNormal());

        std::cout << "Po obliczeniu f. kosztu" << std::endl;

        //std::cout << "Cost function for Gbest particle for exercise 1 for academic criterion of stop: " << theBestParticle1a.costFunctionValuePbest << std::endl;
        //std::cout << "Cost function for Gbest particle for exercise 1 for normal criterion of stop: " << theBestParticle1n.costFunctionValuePbest << std::endl;
        //std::cout << "Cost function for Gbest particle for exercise 2 for academic criterion of stop: "<< theBestParticle2a.costFunctionValuePbest << std::endl;
        //std::cout << "Cost function for Gbest particle for exercise 2 for normal criterion of stop: " << theBestParticle2n.costFunctionValuePbest << std::endl;

        std::cout << "The best particle for Monte Carlo for exercise 1: "
                  << setMC1.monteCarloParticlesVector[0].getCostFunctionValueMinMC() << std::endl;

        //std::cout << "The best particle for Monte Carlo for exercise 2: "
        //          << setMC2.monteCarloParticlesVector[0].getCostFunctionValueMinMC() << std::endl;
    }
    return 0;
}
