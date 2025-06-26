#pragma once
#include "stdlib.h"
#include "memory"

#include "enums.h"
#include "particle.h"
#include "node.h"

using namespace std;

class Cloud
{
    private:
        vector<Particle> particles;
        unique_ptr<Node> node;

        Dimension dimension;

        // range where particles can be created
        static const long long int SPACE_SIZE = 1E6; // km from centre
        static const int SPEED_RANGE = 1000;
        static const int PARTICLE_COUNT = 1000; // 3000
        
        void newParticles2d();
        void newParticles3d();

        void print2d();
        void print3d();

    public:
        void newParticles();

        // todo: create a method for a creating particles with a speed
        void updateParticles();
        void print();

        Cloud(Dimension dimension)
        : dimension(dimension)
        {}
};