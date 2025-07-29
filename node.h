#pragma once

#include "stdlib.h"
#include "math.h"
#include "vector"
#include "memory"
#include <GL/gl.h>

#include "enums.h"
#include "particle.h"
#include "coord.h"

using namespace std;

class Node
{   
    private:
        Dimension   dimension;
        Coord       sizeFrom, sizeTo; // it's a space between x1y1..n1 and x2y2..n2 points
        uint        nestedness; // current daughter node level
        
        uint daughterCount;
        unique_ptr<Node[]> daughters; // daughters = 4 (2d dimension) or 8 (3d dimension) and etc.
        
        Particle    mass_centre;

        static long long int primalFieldSize; // size of first parrent node
        static constexpr float SIMULATION_QUALITY_COEF = 1.0f; // accuracy calculation

    private:
        vector<pair<Coord, Coord>> getDaughterSpaces(); // todo: rename
        uint whatKindRegion(Particle* particle);
        float createDaughters(vector<Particle> particles); // todo: rename split

        double distance(Coord from, Coord to);
        Coord addToEveryAxes(Coord vec, float value);
        void setDaughterField(Coord sizeFrom, Coord sizeTo);

        Node(Dimension dimension, uint nestedness);

        // visual graphic for debug
        void printNodeSectors2d(Coord sizeFrom, Coord sizeTo); // todo: need update
        void printNodeSectors3d(Coord sizeFrom, Coord sizeTo);
        void printInfluenceLines(Coord from, Coord to);

    public:
        void setField(Coord sizeFrom, Coord sizeTo);
        void splitter(vector<Particle> particles);

        Coord oldGravityCalc(Particle* from, Particle* to);
        Coord gravityCalc(Particle* particle);
        
        Node(Dimension dimension);
        Node();
};