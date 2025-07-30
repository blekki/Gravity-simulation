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
        Coord nodeSizeFromCenter;

        Dimension dimension;

        // range where particles can be created
        const long long int SPACE_SIZE = 1E6; // km from centre
        const int PARTICLE_COUNT = 1000; // 3000
        const int SPEED_RANGE = 1000;
        
        const int POINT_WIDTH = 1;
        const float POINT_COLOR[3] = {1.0f, 1.0f, 1.0f};
    
    protected:
        void setDrawingProp();

    public:
        void newParticles();
        // todo: create a method for a creating particles with a speed
        void updateParticles(); // todo: rename "updateFrame" or something as that

        Cloud(Dimension dimension) : dimension(dimension) { 
            node = make_unique<Node>(dimension);
        }
        ~Cloud(){}
};