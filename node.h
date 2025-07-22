#pragma once

#include "stdlib.h"
#include <GL/gl.h>
#include "vector"
#include "memory"

#include "enums.h"
#include "particle.h"
#include "xyz_t.h"

using namespace std;

class Node
{   
    private:
        // todo: sort variables
        unique_ptr<Node[]> node; // daughter nodes (4 or 8)
        uint daughter_count;
        xyz_t x1y1, x2y2;
        Particle mass_centre;
        
        uint nestedness; // current daughter node level
        Dimension dimension;

        static long long int maxFieldSize; // max position from centre for particles
        
        static const uint MAX_NESTEDNESS = 20;
        static constexpr float COEF = 1.0f; // calculation accuracy (node size / dist > coef)

        vector<pair<xyz_t, xyz_t>> division(xyz_t x1y1, xyz_t x2y2);
        uint kindRegion(Particle* particle);
        // float split2d(vector<Particle> particles);
        // float split3d(vector<Particle> particles);
        float splitSpace(vector<Particle> particles);

        void printNodeSectors2d(xyz_t x1y1, xyz_t x2y2);
        void printNodeSectors3d(xyz_t x1y1, xyz_t x2y2);
        void printInfLine(xyz_t from, xyz_t to);


        double dist(xyz_t from, xyz_t to);

    public:
        void setParentFieldSize(xyz_t x1y1, xyz_t x2y2);
        void setFieldSize(xyz_t x1y1, xyz_t x2y2);
        void split(vector<Particle> particles);

        xyz_t oldGravityInf(Particle* from, Particle* to);
        xyz_t gravityInf(Particle* particle);

        Node(Dimension dimension, uint nestedness)
        : dimension(dimension), nestedness(nestedness)
        {}
        
        Node(Dimension dimension)
        : dimension(dimension), nestedness(0)
        {}

        Node(){}
};