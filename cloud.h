#pragma once
#include "stdlib.h"
#include "vector"
#include <GL/gl.h>

#include "particle.h"

using namespace std;

class Cloud
{
    private:
        vector<Particle> particles;
        
        // range where particles can be created
        const uint VALUE_RANGE = 1000000; // 1M km from centre
        const uint SPEED_RANGE = 1000;

        void printsq(xyz_t pos1, xyz_t pos2);
    
    public:

        //  create a new pack dust particles
        void newParticles(uint count);
        void updatePos();
        void print();

        Cloud(){}
};