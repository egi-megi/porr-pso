//
// Created by Agnieszka Jurkiewicz on 28/10/2020.
//

#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
#include <iostream>
#include <vector>

using namespace std;

class Particle
{
public:
    Particle(int vectorDim);
    virtual ~Particle();

    void setVectorDim(int mVectorDim);
    int getVectorDim();
    void setStartPosition();
    void computePosition();
    void computeSpeed(float w, float speedConstant1, float speedConstant2);
    //void computePbest();
    //void computeLbest();

protected:

private:
    int vectorDim;
    vector <double > positionVectors;
    vector <double > speedVectors;
    double Pbest;
    double Lbest;


};
#endif //ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_PARTICLE_H
