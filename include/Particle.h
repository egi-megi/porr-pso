//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Swarm;

class Particle
{
public:
    Particle();
    Particle(int vectorDim,Swarm* s, std::function<double(vector<double>)> functionToOptimize );
    virtual ~Particle();

    void setStartPosition();
    void computePosition();
    void computeSpeed(float w, float speedConstant1, float speedConstant2);
    void computeCostFunctionValue();
    void computeParticlePbest();
    double getParticlePbest();
    double getCostFunctionValuePbest();
    vector <double > getPositionVector();

    double costFunctionValuePbest;
    vector <double > positionVectorsParticlePbest;
    function<double(vector<double>)> getFunctionToOptimize();

protected:

private:
    int vectorDim;
    vector <double > positionVectors;
    vector <double > speedVectors;
    double costFunctionValue;
    double particlePbest;
    Swarm* swarm;
    std::function<double(vector<double>)> functionToOptimize;
    //vector <double > speedVectorsParticlePbest;

};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
