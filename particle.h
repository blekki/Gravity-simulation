#pragma once
#include "xyz_t.h"

using namespace std;

class Particle
{
    private:
        xyz_t pos;
        xyz_t speed;
        float mass;

    public:
        void setPos(xyz_t pos);
        void setSpeed(xyz_t speed);
        void addSpeed(xyz_t speed);

        float getX();
        float getY();
        float getZ();
        xyz_t getXYZ();
        xyz_t getSpeed();
        float getMass();

        void updatePos();

        Particle(xyz_t pos, xyz_t speed)
        : pos(pos), speed(speed), mass(1E9) //1E9 //1.5E14
        {}
        Particle(xyz_t pos, xyz_t speed, float mass) 
        : pos(pos), speed(speed), mass(mass)
        {}
        Particle(){}
};