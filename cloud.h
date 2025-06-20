#pragma once
#include "stdlib.h"
#include "vector"
#include "memory"
#include <GL/gl.h>

#include "particle.h"
#include "node.h"

using namespace std;

class Cloud
{
    private:
        vector<Particle> particles;
        
        // range where particles can be created
        static const int VALUE_RANGE = 1000000; // 1000000; // 1M km from centre
        static const int SPEED_RANGE = 1000;
        static const int PARTICLE_COUNT = 300;

        void printsq(xyz_t pos1, xyz_t pos2);

        unique_ptr<Node> node;
    
    public:

        // create a new pack dust particles
        void newParticles();
        void updatePos();
        void print();


        void updatePos1(); //todo: remove

        Cloud(){}
};