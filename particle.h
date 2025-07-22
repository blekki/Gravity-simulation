#pragma once
#include "coord.h"

using namespace std;

class Particle
{
    private:
        Coord pos;
        Coord speedVec;
        float mass;

    public:
        void setPos(Coord pos);
        void setSpeed(Coord speedVec);
        void addSpeed(Coord speedVec);

        float getX();
        float getY();
        float getZ();
        Coord getPos();
        Coord getSpeed();
        float getMass();

        void updatePos();

        Particle(Coord pos, Coord speedVec)
        : pos(pos), speedVec(speedVec), mass(1E9) //1E9 //1.5E14
        {}
        Particle(Coord pos, Coord speedVec, float mass) 
        : pos(pos), speedVec(speedVec), mass(mass)
        {}
        Particle(){}
};