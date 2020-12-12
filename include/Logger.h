#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_LOGGER_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_LOGGER_H

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

class Logger
{
public:

/// class stores parameters: amountOfParticles, vectorDimension, stopCriterion
/// weight, speedConstant1, speedConstant2, ompSizeOfChunk
    class ParamStruct
    {
        public:
        
        int amountOfParticles;
        int vectorDim; 
        float stopCriterion;
        float weight;
        float speedConst1;
        float speedConst2;
        int ompChunkSize;

        ParamStruct(const int& amount, const int& dim, const float& stop, 
                    const float& w, const float& s1, const float& s2, const int& chunk, Logger* obj);
    };

    std::stringstream stream;
    void logAndClose();
    Logger(const std::string& outputFilename);
    ~Logger();

private:
    std::string date;
    std::ofstream outFile;    
    std::string currentDateTime();  
    void paramsToFile();    


};

#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_LOGGER_H