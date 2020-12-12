#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLEBASE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLEBASE_H

#include <vector>

#include "OptimizationExercisesConfig.h"

class ParticleBase
{
public:
    ParticleBase() = default;
    virtual ~ParticleBase() = default;

    void setStartPosition();
    void computeCostFunctionValue();
    double getCostFunctionValue() const;
    std::vector<double> getPositionVector();

protected:
    double getCoefficientForBoundedPosition(std::vector<double> &v_positionProposition,
        std::vector<double> &v_positionDelta);

    int vectorDim;
    std::vector<double> positionVectors;
    double costFunctionValue;
    OptimizationExercisesConfig *config;
    std::default_random_engine *generator;
};

#endif