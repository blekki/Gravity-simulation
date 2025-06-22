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
        // about field
        unique_ptr<Node> node[4];
        xyz_t x1y1;
        xyz_t x2y2;
        Particle mass_centre;

        // other
        uint level; // current nestedness level

        static const uint NESTEDNESS = 8; // max level
        static constexpr float COEF = 1.0f; // coef of (node size / dist)

    public:
        void setCanvasSize(xyz_t x1y1, xyz_t x2y2);
        double distCube(xyz_t from, xyz_t to);
        
        xyz_t gravityVec2(Particle* from, Particle* to);
        xyz_t gravityVec(Particle* particle);

        float split(vector<Particle> particles);

        void printsq(xyz_t x1y1, xyz_t x2y2);
        void println(xyz_t from, xyz_t to);

        Node(uint level)
        : level(level)
        {}
};