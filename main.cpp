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

    srand (time(NULL));
    std::cout << "Początek obliczeń" << std::endl;

    Swarm s1a(4, 4, new ConfigEx1(-40, 40));
    Particle theBestParticle1a = s1a.findTheBestParticle(0.2, 1.0, 0.1, 0.1, new ConfigStopCriterionAcademic());

    Swarm s1n(4, 4, new ConfigEx1(-40, 40));
    Particle theBestParticle1n = s1n.findTheBestParticle(0.2, 1.0, 0.1, 0.1, new ConfigStopCriterionNormal());

    Swarm s2a(4, 2, new ConfigEx2(-1, 1));
    Particle theBestParticle2a = s2a.findTheBestParticle(1, 0.1, 0.1, 0.1, new ConfigStopCriterionAcademic());

    Swarm s2n(4, 2, new ConfigEx2(-1, 1));
    Particle theBestParticle2n = s2n.findTheBestParticle(0.5, 0.1, 0.1, 0.1, new ConfigStopCriterionNormal());

    std::cout << "Po obliczeniu f. kosztu" << std::endl;
    std::cout << "Gbest particle for exercise 1 for academic criterion of stop: " << theBestParticle1a.costFunctionValuePbest << std::endl;
    std::cout << "Gbest particle for exercise 1 for normal criterion of stop: " << theBestParticle1n.costFunctionValuePbest << std::endl;
    std::cout << "Gbest particle for exercise 2 for academic criterion of stop: " << theBestParticle2a.costFunctionValuePbest << std::endl;
    std::cout << "Gbest particle for exercise 2 for normal criterion of stop: " << theBestParticle2n.costFunctionValuePbest << std::endl;

    return 0;
}
