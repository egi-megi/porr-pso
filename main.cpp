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

//TODO clean code for auto testing - move it to options or new file

enum class TEST
{
    S1AP = 0,
    S1NP, //1
    MC1AP,
    MC1NP,
    S2AP,
    S2NP,
    MC2AP,
    MC2NP,
    S1AS,
    S1NS,
    MC1AS,
    MC1NS,
    S2AS,
    S2NS,
    MC2AS,
    MC2NS //15
};

typedef std::vector<std::string> Parameters;
struct Combination
{   
    std::string algorithm;
    std::string task;
    std::string stopCondition;
    std::string cpuBehaviour;

    Combination(Parameters params) : algorithm(params[0]), task(params[1]), stopCondition(params[2]), cpuBehaviour(params[3]){};
};

Combination getTestCombination(TEST val) 
{   
    Parameters params;

    switch (val) {
	case TEST::S1AP: params = Parameters {"Swarm", "Task1", "Academic", "Parallel"}; break;
    case TEST::S1NP: params = Parameters {"Swarm", "Task1", "Normal", "Parallel"}; break;
    case TEST::MC1AP: params = Parameters {"MonteCarlo", "Task1", "Academic", "Parallel"}; break;
    case TEST::MC1NP: params = Parameters {"MonteCarlo", "Task1", "Normal", "Parallel"}; break;
    case TEST::S2AP: params = Parameters {"Swarm", "Task2", "Academic", "Parallel"}; break;
    case TEST::S2NP: params = Parameters {"Swarm", "Task2", "Normal", "Parallel"}; break;
    case TEST::MC2AP: params = Parameters {"MonteCarlo", "Task2", "Academic", "Parallel"}; break;
    case TEST::MC2NP: params = Parameters {"MonteCarlo", "Task2", "Normal", "Parallel"}; break;
    case TEST::S1AS: params = Parameters {"Swarm", "Task1", "Academic", "Serial"}; break;
    case TEST::S1NS: params = Parameters {"Swarm", "Task1", "Normal", "Serial"}; break;
    case TEST::MC1AS: params = Parameters {"MonteCarlo", "Task1", "Academic", "Serial"}; break;
    case TEST::MC1NS: params = Parameters {"MonteCarlo", "Task1", "Normal", "Serial"}; break;
    case TEST::S2AS: params = Parameters {"Swarm", "Task2", "Academic", "Serial"}; break;
    case TEST::S2NS: params = Parameters {"Swarm", "Task2", "Normal", "Serial"}; break;
    case TEST::MC2AS: params = Parameters {"MonteCarlo", "Task2", "Academic", "Serial"}; break;
    case TEST::MC2NS: params = Parameters {"MonteCarlo", "Task2", "Normal", "ParaSerialllel"}; break;
    }
    return Combination (params);
} 


int main(int argc, char* argv[])
{
    Logger* logger;
    Options* options = new Options();

    if(argc > 1)
    {
        // It seems that the user wants manual control

        options->stopCriterionConfig = new ConfigStopCriterionAcademic();
        options->optimizationExerciseConfig = new ConfigEx2();
        options->verbose = false;
        options->stopCriterionThreshold = 0.01;
        options->setLowerBoundBoxInitialization(-40);
        options->setUpperBoundBoxInitialization(-30);
        options->communication = Options::CommunicationType::LOCAL_BEST;

        InputParser::parse(options, argc, argv);

        std::string logPath = "logs/log_" + options->optionsToString(true) + "_manual.txt";
        std::string particlesPath = "logs/particlesLog_" + options->optionsToString(true) + "_manual.txt";

        logger = new Logger(options, logPath, particlesPath, true, false);

        Swarm s1a(options, logger);

        double chi = 0.72984, c1 = 2.05, c2 = 2.05;
        double w = chi;
        c1 = chi * c1;
        c2 = chi * c2;

        SwarmParticle s1a_best = s1a.findTheBestParticle(w, c1, c2);
        printf("Best particle f(s1a_best) = %lf\n", s1a_best.getCostFunctionValue());

        // MonteCarlo m1a(options, logger);
        // MonteCarloParticle m1a_best = m1a.findTheBestParticle(.1, .01);
        // printf("Best particle f(m1a_best) = %lf\n", m1a_best.getCostFunctionValue());

        logger->saveToFileAndClose();
        delete options->stopCriterionConfig;
        delete options->optimizationExerciseConfig;
        delete logger;
    }
    else
    {
        // algorithm, task, stop condition, parallel or serial
        // s = 0, task1 = 0, a = 0, P = 0 

        std::vector<std::string> taskTypes = {"s1aP","s1nP","mc1aP","mc1nP","s2aP","s2nP","mc2aP","mc2nP",
                                            "s1aS","s1nS","mc1aS","mc1nS","s2aS","s2nS","mc2aS","mc2nS"};
                    
        std::vector<int> chosenTests{4};//tests ids you want to run

        for (auto testId : chosenTests)
        {

            Combination combination = getTestCombination(static_cast<TEST>(testId));

            std::string logPath = "logs/log_" + options->optionsToString(true) + "_" + taskTypes[testId] + ".txt";
            std::string particlesPath = "logs/particlesLog_" + options->optionsToString(true) + "_" + taskTypes[testId] + ".txt";

            if (combination.stopCondition == "Academic")
            {
                options->stopCriterionConfig = new ConfigStopCriterionAcademic();
            }
            else
            {
                options->stopCriterionConfig = new ConfigStopCriterionNormal(0.1); // TODO add treshold variable
            }

            logger = new Logger(options, logPath, particlesPath, true);

            if (combination.algorithm == "Swarm")
            {
                if (combination.task == "Task1")
                {
                    options->optimizationExerciseConfig = new ConfigEx1();

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
                    // TODO add task2 for swarm
                }
            }
            else
            {
                if (combination.task == "TASK1")
                {
                    MonteCarlo mc1a(options, logger);
                    MonteCarloParticle mc1a_best = mc1a.findTheBestParticle(.01, .1);

                    printf("Best particle f(mc1a_best) = %lf\n", mc1a_best.getCostFunctionValue());
                }
                else
                {
                    //TODO add task 2 for monte carlo
                }
            }

            logger->saveToFileAndClose();
            delete options->optimizationExerciseConfig;
            delete options->stopCriterionConfig;
            delete logger;
        }
    }

    delete options;

    return 0;
}