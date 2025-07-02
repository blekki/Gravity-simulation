#pragma once
#include "stdlib.h"
#include "memory"

#include "enums.h"
#include "particle.h"
#include "node.h"

using namespace std;

class Cloud
{
    protected:
        vector<Particle> particles;
        unique_ptr<Node> node;

        Dimension dimension;

        // range where particles can be created
        const long long int SPACE_SIZE = 1E6; // km from centre
        const int SPEED_RANGE = 1000;
        const int PARTICLE_COUNT = 300; // 3000
        const int POINT_WIDTH = 1;
        const float POINT_COLOR[3] = {1.0f, 1.0f, 1.0f};
        
        void newParticles2d();
        void newParticles3d();

        // void print2d();
        // void print3d();

    public:
        void newParticles();
        // todo: create a method for a creating particles with a speed
        void updateParticles();
        // void print();

        Cloud(Dimension dimension)
        : dimension(dimension)
        {}
        ~Cloud(){}
};