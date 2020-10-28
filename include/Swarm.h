//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H

#include <iostream>

using namespace std;

class Swarm
{
public:
    Swarm();
    virtual ~Swarm();

    void computePbestVector();
    void computeLbestVector();

protected:

private:
    double PbestVector;
    double LbestVector;



};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
