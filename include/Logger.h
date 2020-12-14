#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_LOGGER_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_LOGGER_H

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include "Options.h"

class Logger
{
public:
    
    Options *options;

    //streams
    std::stringstream stream;
    std::stringstream pStream;

    //paths
    std::string mainLogPath;
    std::string particlesLogPath;

    //flags
    bool isLogAllData;
    bool isLoggerActive;
    bool isLogOnlyBest;

    std::string currentDateTime();
    void saveToFileAndClose();

    void sendToParticlesStream(const int &iter, const float &cost, const float &pos1, const float &pos2, const float &speed1, const float &speed2);
    void sendAllParticlesStream(const int &iter, const int &id, const float &pos1, const float &pos2, const float &speed1, const float &speed2, const float &cost);
    void saveParticleStreamBuffer();
    void setActivityOfLogger(const bool& isActive);

    Logger()=default;
    Logger(Options *options, const std::string &mainLogPath, const std::string &particlesLogPath = "", const bool &isLogAll = false, const bool &isActive = true);
    //Logger(const std::string& outputFilename, const std::string& particlesFile, const int& dim =-1, const bool& isLogAll=false);
    ~Logger();

private:
    std::string date;
    std::ofstream *outFile;
    std::ofstream *outParticlesFile;
};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_LOGGER_H