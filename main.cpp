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
#include "include/AutoTest.h"

#include <iostream>

int main(int argc, char* argv[])
{
    Logger* logger;
    Options* options;

    // taskTypes legend: algorithm, task, stop condition, parallel or serial

    std::vector<int> chosenTests{static_cast<int>(TEST::MC2AP)};//tests ids you want to run

    for (auto testId : chosenTests)
    {
        Combination combination (static_cast<TEST>(testId));       
        options = new Options();
        if (combination.task == "Task1")
        {
            options->optimizationExerciseConfig = new ConfigEx1();
        }
        else
        {
            options->optimizationExerciseConfig = new ConfigEx2();
        }

        std::string logPath = "../logs/log_" + options->optionsToString(true) + "_" + combination.taskTypes[testId] + ".txt";
        std::string particlesPath = "../logs/particlesLog_" + options->optionsToString(true) + "_" + combination.taskTypes[testId] + ".txt";
 
        InputParser::parse(options, argc, argv); // TODO parser needs to be solved in loop differently

        if (combination.stopCondition == "Academic")
        {
            options->stopCriterionConfig = new ConfigStopCriterionAcademic();
        }
        else
        {
            options->stopCriterionConfig = new ConfigStopCriterionNormal(0.01); // TODO add treshold variable
        }
        //options->verbose = false;
        logger = new Logger(options, logPath, particlesPath, true);
        
        // run if this is the first run with the same parameters (dimension and particlesNumber) to log start position of particles
        //options->prepareAndActivateWriteLogger();
        options->prepareAndActivateReadLogger();
   
        if (combination.algorithm == "Swarm")
        {
            if (combination.task == "Task1")
            {
                Swarm s1a(options, logger);

                double chi = 0.72984, c1 = 2.05, c2 = 2.05;
                double w = chi;
                c1 = chi * c1;
                c2 = chi * c2;

                SwarmParticle s1a_best = s1a.findTheBestParticle(w, c1, c2);
                printf("Best particle f(s1a_best) = %lf\n", s1a_best.getCostFunctionValue());
            }
            else
            {
                Swarm s2a(options, logger);

                double chi = 0.72984, c1 = 2.05, c2 = 2.05;
                double w = chi;
                c1 = chi * c1;
                c2 = chi * c2;

                SwarmParticle s2a_best = s2a.findTheBestParticle(w, c1, c2);
                printf("Best particle f(s2a_best) = %lf\n", s2a_best.getCostFunctionValue());
            }
        }
        else
        {
            if (combination.task == "Task1")
            {
                MonteCarlo mc1a(options, logger);
                MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(2, .01);

                printf("Best particle f(mc1a_best) = %lf\n", mc1a_best.getCostFunctionValue());
            }
            else
            {
                MonteCarlo mc2a(options, logger);
                MonteCarloParticle mc2a_best = mc2a.findTheBestParticle(2, .01);

                printf("Best particle f(mc2a_best) = %lf\n", mc2a_best.getCostFunctionValue());
            }
        }

        logger->saveToFileAndClose();
        delete options->optimizationExerciseConfig;
        delete options->stopCriterionConfig;
        delete options;
        delete logger;
    }  

    return 0;
}