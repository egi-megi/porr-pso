#include "include/SwarmParticle.h"
#include "include/Swarm.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include "include/MonteCarloParticle.h"
#include "include/MonteCarlo.h"
#include "include/Options.h"
#include "include/InputParser.h"
#include "include/Logger.h"


#include <iostream>

int main(int argc, char* argv[])
{
    // OLD LOGGER
    // int dim = 2;
    // Logger log_temp;
    // std::string date = log_temp.currentDateTime();
    // std::string bestParticlesLogFileName = "../logs/log_" + date + ".txt";
    // std::string allParticlesLogFileName = "../logs/particlesLog_" + date + ".txt";
    // // Logger* log = new Logger("../log.txt", "../particlesLog.txt", dim, true);
    // Logger* log = new Logger(bestParticlesLogFileName, allParticlesLogFileName, dim, true);
    // Logger::ParamStruct params (25, dim, 0.001f, 0.8f, 0.1f, 0.2f, 1000, log);

    Options* options = new Options();
    options->optimizationExerciseConfig = new ConfigEx1();
    options->stopCriterionConfig = new ConfigStopCriterionAcademic();
    
    //InputParser::parse(options, argc, argv);

    // algorithm, task, stop condition, paraller or serial
     std::vector<std::string> taskTypes = {"s1aP","s1nP","mc1aP","mc1nP","s2aP","s2nP","mc2aP","mc2nP",
                                           "s1aS","s1nS","mc1aS","mc1nS","s2aS","s2nS","mc2aS","mc2nS"};
    int testID = 0;      
    //std::vector<int> testTypeSequence = {0,0,0,0}; // propozycja automatyzacji                          

    std::string logPath = "logs/log_" + options->optionsToString(true) + "_" + taskTypes[testID] + ".txt";
    std::string particlesPath = "logs/particlesLog_" + options->optionsToString(true) + "_" + taskTypes[testID] + ".txt";
    Logger* log = new Logger(options, logPath, particlesPath, true);  

    Swarm s1a(options, log);
    SwarmParticle s1a_best = s1a.findTheBestParticle(0.8, .1, .2);
    
    printf("Best particle f(s1a_best) = %lf\n", s1a_best.getCostFunctionValue());

    // MonteCarlo mc1a(options, log);
    // MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(1, 8);

    // printf("Best particle f(mc1a_best) = %lf\n", mc1a_best.getCostFunctionValue());

    log->saveToFileAndClose();
    delete options->optimizationExerciseConfig;
    delete options->stopCriterionConfig;
    delete options;
    delete log;

    return 0;
}