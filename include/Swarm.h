#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H

#include "SwarmParticle.h"
#include "ConfigStopCriterionAcademic.h"
#include "ConfigStopCriterionNormal.h"
#include "StopCriterionConfig.h"
#include "Options.h"
#include "Logger.h"

#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

using namespace std;

class Swarm
{
public:
    Swarm() = default;
    Swarm(Options *mOptions, Logger *log);
    virtual ~Swarm() = default;

    void makeSwarm();
    void computeGbest(SwarmParticle *particle);
    SwarmParticle findTheBestParticle(float criterionStopValue, float w, float speedConstant1,
        float speedConstant2, StopCriterionConfig *configStop);
    SwarmParticle findTheBestParticle(float w, float speedConstant1, float speedConstant2);
    std::pair<SwarmParticle, SwarmParticle> globalBestParticle;

private:
    vector<double> getPositionOfBetterParticle(SwarmParticle& p_1, SwarmParticle& p_2);
    void psoLogger(const int& iteration, const double& cost);
    int amountOfParticles;
    int vectorDim;
    vector<SwarmParticle> swarm;
    Options *options;
    Logger *log;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_SWARM_H