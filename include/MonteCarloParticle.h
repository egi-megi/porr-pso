//
// Created by Agnieszka Jurkiewicz on 09/12/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H
#include <iostream>
#include <vector>
#include <functional>
#include "OptimizationExercisesConfig.h"
#include <random>
//#include <omp.h>
using namespace std;

class MonteCarloParticle {
        public:
        MonteCarloParticle();
        MonteCarloParticle(int vectorDim, Swarm* s, OptimizationExercisesConfig* config, std::default_random_engine* generator);
        MonteCarloParticle(int vectorDim, Swarm* s, OptimizationExercisesConfig* config);
        virtual ~MonteCarloParticle();

        void setStartPosition();
        void setStartSpeed();
#ifdef OPEN_MP_MONTE_CARLO
        void computePosition(float w, float speedConstant1, float speedConstant2, std::default_random_engine* gen);
    void computeSpeed(float w, float speedConstant1, float speedConstant2, int i, std::default_random_engine* gen);
#else
        void computePosition(float w, float speedConstant1, float speedConstant2);
        void computeSpeed(float w, float speedConstant1, float speedConstant2, int i);
#endif
        void computeCostFunctionValue();
        void computeParticlePbest();
        double getCostFunctionValue();
        double getCostFunctionValuePbest();
        vector <double > getPositionVector();

        double costFunctionValuePbest;
        vector <double > positionVectorsParticlePbest;

        protected:

        private:
        int vectorDim;
        vector <double > positionVectors;
        vector <double > speedVectors;
        vector <double > tempSpeedVectors;
        double costFunctionValue;
        Swarm* swarm;
        OptimizationExercisesConfig* config;
        std::default_random_engine* generator;
    };



#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_MONTECARLOPARTICLE_H
