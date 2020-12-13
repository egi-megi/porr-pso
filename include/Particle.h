#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLEBASE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLEBASE_H

#include <vector>
#include <random>

#include "OptimizationExercisesConfig.h"

class Particle
{
public:
    Particle() = default;
    virtual ~Particle() = default;

    void setStartPosition(std::default_random_engine &gen);
    void computeCostFunctionValue();
    double getCostFunctionValue() const;
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
};

#endif