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
        const int VALUE_RANGE = 10; // 1000000; // 1M km from centre
        const int SPEED_RANGE = 1000;

        void printsq(xyz_t pos1, xyz_t pos2);

        // teoreticaly: Node node x4;
        unique_ptr<Node> node;
    
    public:

        // create a new pack dust particles
        void newParticles(uint count);
        void updatePos();
        void print();


        void updatePos1(); //todo: remove

        Cloud(){}
};