#include "include/Options.h"
#include "include/ConfigStopCriterionNormal.h"
#include "include/ConfigStopCriterionAcademic.h"
#include "include/ConfigEx1.h"
#include "include/ConfigEx2.h"
#include "include/SwarmParticle.h"
#include "include/MonteCarloParticle.h"
#include "include/Swarm.h"
#include "include/MonteCarlo.h"
#include "include/InputParser.h"
#include "include/Logger.h"


#include <iostream>

#include <iostream>

#include <iostream>

int main(int argc, char* argv[])
{
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

    double chi = 0.72984, c1 = 2.05, c2 = 2.05;
    double w = chi;
    c1 = chi*c1;
    c2 = chi*c2;

    SwarmParticle s1a_best = s1a.findTheBestParticle(w, c1, c2);
    
    printf("Best particle f(s1a_best) = %lf\n", s1a_best.getCostFunctionValue());

    // MonteCarlo mc1a(options);
    // MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(.01, .1);

    // printf("Best particle f(mc1a_best) = %lf\n", mc1a_best.getCostFunctionValue());

    log->saveToFileAndClose();
    delete options->optimizationExerciseConfig;
    delete options->stopCriterionConfig;
    delete options;
    delete log;

    return 0;
}