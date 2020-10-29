//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#include <iostream>
#include <vector>


using namespace std;

class Swarm;

class Particle
{
public:
    //Particle();
    Particle(int vectorDim,Swarm* s);
    virtual ~Particle();

    void setVectorDim(int mVectorDim);
    int getVectorDim();
    void setStartPosition();
    void computePosition();
    void computeSpeed(float w, float speedConstant1, float speedConstant2);
    void computeCostFunctionValueZad1();
    void computeCostFunctionValueZad2();
    void computeParticlePbest();
    void computeParticleLbest();
    double getParticlePbest();
    double getCostFunctionValuePbest();

    double costFunctionValuePbest;
    vector <double > positionVectorsParticlePbest;

protected:

private:
    int vectorDim;
    vector <double > positionVectors;
    vector <double > speedVectors;
    double costFunctionValue;
    double particlePbest;
    Swarm* swarm;
    //vector <double > speedVectorsParticlePbest;

};


#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
