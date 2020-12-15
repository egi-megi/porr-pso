#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H

#include "OptimizationExercisesConfig.h"
#include "StopCriterionConfig.h"

#include <sstream>
#include <iostream>
#include <fstream>

class StopCriterionConfig;
class Logger;

class Options
{
public:
    Options();
      virtual ~Options() = default;

    OptimizationExercisesConfig* optimizationExerciseConfig;
    StopCriterionConfig* stopCriterionConfig;
    
    double stopCriterionThreshold;
    int amountOfParticles;
    int dimension;

    bool verbose;
    bool timing;

    std::vector<std::vector<double> > particlesFromFile;

    bool filenameEqualsParameters;
    bool fileReadyToReadFrom;
    bool isSaveStartPosition;

    std::string particlesStartPositionsFileName;
    std::stringstream particlePositionStream;

    std::ifstream* inputFile;
    std::ofstream* outputFile;

    //activate logger
    void prepareAndActivateWriteLogger();
    void prepareAndActivateReadLogger();

    //load
    void loadStartPositionFromFile();
    void checkFileName(); // check filename if it makes sense to load this data
   
    //save
    void addStartPositionToBuffer(std::vector<double> positionsVector, const int& id);  
    void createFileNameFromParameters();
    void openOutputFile();
    void openInputFile();
    void readBufferAndCloseFile();
    
    std::string optionsToString(const bool& useDate);
    std::string currentDateTime();

    enum CommunicationType {
        GLOBAL_BEST,
        LOCAL_BEST
    };
    CommunicationType communication;
};


#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_OPTIONS_H