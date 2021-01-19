#include "../include/MonteCarlo.h"
#include "../include/MonteCarloParticle.h"
#include "../include/Options.h"
#include "../include/Timer.h"

#include <stdio.h>
#include <random>
#include <time.h>
#ifdef OPEN_MP_SWARM
#include <omp.h>
#endif

MonteCarlo::MonteCarlo(Options *mOptions, Logger* _log) :
    amountOfParticles{mOptions->amountOfParticles}, vectorDim{mOptions->dimension},
    v_particles(mOptions->amountOfParticles), options{mOptions}, log{_log} 
{
#ifdef OPEN_MP_SWARM   
    printf("Welcome to OpenMP version!\n");
#else
    printf("Welcome to sequential version!\n");
#endif
    Timer t1;
    makeMonteCarlo();
    if(options->timing)
        printf("MonteCarlo::MonteCarlo: Initialization took %.2lf s\n", t1.click());
}

#ifdef OPEN_MP_SWARM
void MonteCarlo::makeMonteCarlo()
{
#pragma omp parallel
{
    std::default_random_engine rand_engine;
    rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));
#pragma omp for
    for(int i = 0; i < amountOfParticles; i++)
        v_particles[i] = MonteCarloParticle(options, rand_engine);
}

    globalBestParticle.first = v_particles[0];
    for(int i = 1; i < amountOfParticles; i++)
    {
        if (v_particles[i].getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
            globalBestParticle.first = v_particles[i];
    }
}
#else
void MonteCarlo::makeMonteCarlo()
{
    std::default_random_engine rand_engine;
    rand_engine.seed(time(NULL));
    for(int i = 0; i < amountOfParticles; i++)
        v_particles[i] = MonteCarloParticle(options, rand_engine);

    globalBestParticle.first = v_particles[0];
    for(int i = 1; i < amountOfParticles; i++)
    {
        if (v_particles[i].getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
            globalBestParticle.first = v_particles[i];
    }
}
#endif

void MonteCarlo::computeGlobalBest(MonteCarloParticle *particle)
{
    if(particle == nullptr)
        return;
    else if (particle->getCostFunctionValue() < globalBestParticle.first.getCostFunctionValue())
    {
        globalBestParticle.second = globalBestParticle.first;
        globalBestParticle.first = *particle;
    }
}

#ifdef OPEN_MP_SWARM
MonteCarloParticle MonteCarlo::findTheBestParticle(float criterionStopValue,
    float sigma, float T, StopCriterionConfig *configStop)
{
    Timer t1;

    bool foundSolution = false;
    int iteration_number = 0;
    int threadsCompleted = 0;
#pragma omp parallel
    {
        std::default_random_engine rand_engine;
        rand_engine.seed((omp_get_thread_num() + 1) * time(NULL));

        MonteCarloParticle *bestParticleInIteration = nullptr;

        int threads = omp_get_num_threads();

        while(!foundSolution)
        {
#pragma omp for schedule(static) nowait
            for(int i = 0; i < amountOfParticles; i++)
            {
                v_particles[i].computePosition(sigma, T, rand_engine);

                if (bestParticleInIteration == nullptr)
                    bestParticleInIteration = &v_particles[i];
                else if (v_particles[i].getCostFunctionValue() < bestParticleInIteration->getCostFunctionValue())
                    bestParticleInIteration = &v_particles[i];
            }

#pragma omp critical
            computeGlobalBest(bestParticleInIteration);
            bestParticleInIteration = nullptr;

#pragma omp critical
            {
                threadsCompleted++;
                if(threadsCompleted >= threads)
                {
                    threadsCompleted -= threads;

                    if (options->verbose)
                    {
                        double cost = globalBestParticle.first.getCostFunctionValue();
                        printf("MonteCarlo::findTheBestParticle: iteration = %d, globalBestParticle.first = %lf\n",
                               iteration_number, cost);
                        //log
                        monteCarloLogger(iteration_number, cost);
                    }

                    iteration_number++;

                    if (!configStop->computeStopCriterion(criterionStopValue, globalBestParticle))
                        foundSolution = true;
                }
            }       
        }
    }

    if(options->timing)
        printf("MonteCarlo::findTheBestParticle: Solution took %.2lf s\n", t1.click());

    return globalBestParticle.first;
}
#else
MonteCarloParticle MonteCarlo::findTheBestParticle(float criterionStopValue,
    float sigma, float T, StopCriterionConfig *configStop)
{
    Timer t1;

    std::default_random_engine rand_engine;
    rand_engine.seed(time(NULL));

    int iteration_number = 0;
    while(configStop->computeStopCriterion(criterionStopValue, globalBestParticle))
    {
        for(auto &particle: v_particles)
        {
            particle.computePosition(sigma, T, rand_engine);
            computeGlobalBest(&particle);
        }
        if (options->verbose)
        { 
            double cost = globalBestParticle.first.getCostFunctionValue();
            printf("MonteCarlo::findTheBestParticle: iteration = %d, globalBestParticle.first = %lf\n",
                   iteration_number, globalBestParticle.first.getCostFunctionValue());
            //log
            monteCarloLogger(iteration_number, cost);
        }
        iteration_number++;
    }

    if(options->timing)
        printf("MonteCarlo::findTheBestParticle: Solution took %.2lf s\n", t1.click());

    return globalBestParticle.first;
}
#endif

MonteCarloParticle MonteCarlo::findTheBestParticle(float sigma, float T)
{
    return findTheBestParticle(options->stopCriterionThreshold, sigma, T,
        options->stopCriterionConfig);
}

void MonteCarlo::monteCarloLogger(const int& iteration, const double& cost)
{
    if (log->isLoggerActive)
    {
        log->stream << iteration << ',' << cost << ',' << globalBestParticle.first.getParticleId() << '\n';
    }

    if (log->isLoggerActive) //only for n=2
    {
        if (log->isLogAllData)
        {
            for (auto p : v_particles)
            {
                log->sendAllParticlesStream(iteration, p.getParticleId(), p.getPositionVector()[0], p.getPositionVector()[1], -1, -1, p.getCostFunctionValue());
            }
            log->saveParticleStreamBuffer();
        }
        else if (log->isLogOnlyBest)
        {
            MonteCarloParticle p = globalBestParticle.first;
            log->sendToParticlesStream(iteration, cost, p.getPositionVector()[0], p.getPositionVector()[1], -1, -1);
        }
    }
}