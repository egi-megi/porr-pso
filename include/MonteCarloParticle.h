#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H

#include "Particle.h"
#include "Options.h"

class MonteCarloParticle : public Particle
{
public:
    MonteCarloParticle() = default;
    MonteCarloParticle(Options *mOptions, std::default_random_engine &gen);
    MonteCarloParticle(Options *mOptions, std::default_random_engine &gen, std::vector<double> _positionVector);
    virtual ~MonteCarloParticle() = default;

    void computePosition(float sigma, float T, std::default_random_engine &gen);

private:
    Options *options;
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H