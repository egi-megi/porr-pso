#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H

#include "OptimizationExercisesConfig.h"
#include "Options.h"

#include <vector>
#include <random>

class Options;

class Particle
{
public:
    Particle() = default;
    virtual ~Particle() = default;

    void setStartPosition(std::default_random_engine &gen);
    void computeCostFunctionValue();
    double getCostFunctionValue() const;
    double getCostFunctionValue(std::vector<double> &v_position) const;
    std::vector<double> getPositionVector();
    bool isReady() const;

protected:
    double getCoefficientForBoundedPosition(std::vector<double> &v_positionProposition,
        std::vector<double> &v_positionDelta);

    int vectorDim;
    std::vector<double> positionVectors;
    double costFunctionValue;
    OptimizationExercisesConfig *config;
    bool ready = false;

    Options *options;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H