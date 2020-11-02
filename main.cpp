#include <iostream>
#include "include/Particle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include <math.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main() {

    srand (time(NULL));
    std::cout << "Hello, World!" << std::endl;

    Swarm s(4, 4, new ConfigEx1());
    Particle theBestParticle = s.findTheBestParticle(0.2, 1.0, 0.1, 0.1);

    std::cout << "Po obliczeniu f. kosztu" << std::endl;
    std::cout << theBestParticle.costFunctionValuePbest << std::endl;

    return 0;
}
