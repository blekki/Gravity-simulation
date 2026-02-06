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
        Coord nodeSizeFromCenter;

        Dimension dimension;

        // range where particles can be created
        const float SPACE_SIZE = 1E4;       // km from centre
        const int PARTICLE_COUNT = 1000;
        // const int SPEED_RANGE = 1000;
        
        const int POINT_WIDTH = 1;
        const float POINT_COLOR[3] = {1.0f, 1.0f, 1.0f};
    
    private:
        void newParticles();
        void addNewParticle(Particle particle);
        void addNewParticle(Coord position, Coord speed);
        void setDrawingProp();
        Coord asNDC(Coord coord);

    public:
        // todo: create a method for a creating particles with a speed
        void updateParticles();
        void print();
        void printNodeSectors();

        Cloud(Dimension dimension);

};