#pragma once

#include "stdlib.h"
#include <GL/gl.h>
#include "vector"
#include "memory"
#include "math.h"

#include "particle.h"
#include "xyz_t.h"

#include "iostream" // todo: remove

#include <unistd.h>

using namespace std;

class Node
{   
    private:
        unique_ptr<Node> node[4]; // daughter nodes
        xyz_t x1y1, x2y2;
        Particle mass_centre;
        uint nestedness; // current daughter node level

        static int maxFieldSize; // max position from centre for particles
        
        static const uint MAX_NESTEDNESS = 8;
        static constexpr float COEF = 1.0f; // calculation accuracy (node size / dist > coef)

    public:
        void setParentFieldSize(xyz_t x1y1, xyz_t x2y2);
        void setFieldSize(xyz_t x1y1, xyz_t x2y2);
        float split(vector<Particle> particles);
        
        double dist(xyz_t from, xyz_t to);
        xyz_t oldGravityInf(Particle* from, Particle* to);
        xyz_t gravityInf(Particle* particle);

        // for debug
        void printNodeSectors(xyz_t x1y1, xyz_t x2y2);
        void printInfLine(xyz_t from, xyz_t to);

        Node(uint nestedness) : nestedness(nestedness) {}
        Node() : nestedness(0) {}
};