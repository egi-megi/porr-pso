#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H

#include "OptimizationExercisesConfig.h"
#include "StopCriterionConfig.h"

#include <sstream>

class StopCriterionConfig;
class Logger;

class Options
{
public:
    Options();
    virtual ~Options() = default;

    void setLowerBoundBoxInitialization(const double &bound);
    void setUpperBoundBoxInitialization(const double &bound);
    double& getLowerBoundBoxInitialization();
    double& getUpperBoundBoxInitialization();

    OptimizationExercisesConfig* optimizationExerciseConfig;
    StopCriterionConfig* stopCriterionConfig;
    
    double stopCriterionThreshold;
    int amountOfParticles;
    int dimension;

    bool verbose;
    bool timing;

    std::string optionsToString(const bool& useDate);
    std::string currentDateTime();

    enum CommunicationType {
        GLOBAL_BEST,
        LOCAL_BEST
    };
    CommunicationType communication;

private:
    bool isSetLowerBoundBoxInitialization;
    double lowerBoundBoxInitialization;
    bool isSetUpperBoundBoxInitialization;
    double upperBoundBoxInitialization;
};


#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H