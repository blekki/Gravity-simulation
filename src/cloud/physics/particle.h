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


        // void setPosXY(float range) {
        void setRandomPosXY(float range) {
            int radius = GENERATION_ACCURACY;
            int diameter = radius * 2;

            // generate value from -1.0f to 1.0f
            float x = (rand() % diameter - radius) / float(radius);
            float y = (rand() % diameter - radius) / float(radius);
            
            // convert into space coord
            pos.x = x * range;
            pos.y = y * range;
        }

        void setRandomPosXYZ(float range) {
            uint radius = GENERATION_ACCURACY;
            uint diameter = radius * 2;

            // generate value from -1.0f to 1.0f
            setRandomPosXY(range);
            float z = (rand() % diameter - radius) / float(radius);

            // convert into space coord
            pos.z = z * range;
        }



        Particle(Coord pos, Coord speedVec)
        : pos(pos), speedVec(speedVec), mass(DEFAULT_MASS) // weight of small asteroid in tonns
        {}
        Particle(Coord pos, Coord speedVec, float mass) 
        : pos(pos), speedVec(speedVec), mass(mass)
        {}
        Particle(){
            pos      = Coord(0, 0, 0);
            speedVec = Coord(0, 0, 0);
            mass     = DEFAULT_MASS;
        }
};