#include <iostream>

#include "include/SwarmParticle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include "include/MonteCarloParticle.h"
#include "include/MonteCarlo.h"

int main()
{
    MonteCarlo mc1a(10, 3, new ConfigEx1());
    MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(0.1, 1, 8, new ConfigStopCriterionAcademic());

    std::cout << "Final cost function for mc1a = " << mc1a_best.getCostFunctionValue() <<std::endl;

    // Swarm s1a(200000, 50, new ConfigEx1());
    // SwarmParticle theBestParticle1a = s1a.findTheBestParticle(0.1, 0.8, .1, .2, new ConfigStopCriterionAcademic());

    //Swarm s1n(100, 10, new ConfigEx1());
    //Particle theBestParticle1n = s1n.findTheBestParticle(0.1, 1.0, 0.1, 0.1, new ConfigStopCriterionNormal());

    //Swarm s2a(1000, 40, new ConfigEx2());
    //Particle theBestParticle2a = s2a.findTheBestParticle(0.5, 0.00001, 0.00001, 0.00001, new ConfigStopCriterionAcademic());

    //Swarm s2n(100, 4, new ConfigEx2());
    //Particle theBestParticle2n = s2n.findTheBestParticle(0.5, 0.1, 0.1, 0.1, new ConfigStopCriterionNormal());

    // std::cout << "Cost function for Gbest particle for exercise 1 for academic criterion of stop: " << theBestParticle1a.getCostFunctionValue() << std::endl;
    //std::cout << "Cost function for Gbest particle for exercise 1 for normal criterion of stop: " << theBestParticle1n.costFunctionValuePbest << std::endl;
    //std::cout << "Cost function for Gbest particle for exercise 2 for academic criterion of stop: "<< theBestParticle2a.costFunctionValuePbest << std::endl;
    //std::cout << "Cost function for Gbest particle for exercise 2 for normal criterion of stop: " << theBestParticle2n.costFunctionValuePbest << std::endl;

    return 0;
}