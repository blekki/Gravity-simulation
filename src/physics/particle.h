#pragma once
#include "coord.h"

using namespace std;

class Particle
{
    private:
        Coord pos;
        Coord speedVec;
        float mass;

        static const float DEFAULT_MASS;
        static const int GENERATION_ACCURACY;

    private:
        void resetPos();
        void resetSpeed();
        void setDefaultMass();

    public:
        void setPos(Coord pos);
        void setRandomPosXY(float range);
        void setRandomPosXYZ(float range);
        void updatePos();
        void setSpeed(Coord speedVec);
        void addSpeed(Coord speedVec);

        float getX();
        float getY();
        float getZ();
        Coord getPos();
        Coord getSpeed();
        float getMass();

        Particle();
        Particle(Coord pos, Coord speedVec);
        Particle(Coord pos, Coord speedVec, float mass);
};