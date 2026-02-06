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
        static constexpr float SIMULATION_QUALITY_COEF = 2.0f; // accuracy calculation
        
        // static const float G = 6.6742E-11;
        static constexpr float LOWER_CALC_BORDER = 100;
        static const Coord NO_INFLUENCE;

    private:
        double distance(Coord from, Coord to);
        Coord addToEveryAxes(Coord vec, float value);

        vector<pair<Coord, Coord>> getDaughterSpaces();
        uint whatKindRegion(Particle* particle);
        float createDaughters(vector<Particle> particles);
        void setDaughterField(Coord sizeFrom, Coord sizeTo);

        // visual graphic for debug
        void printNodeSectors2d(); // todo: need update
        void printNodeSectors3d();
        void printInfluenceLines(Coord from, Coord to);

        // private constructor
        Node(Dimension dimension, uint nestedness);

    public:
        void setField(Coord sizeFrom, Coord sizeTo);
        void splitter(vector<Particle> particles);      // todo: rename to "split" or the same way

        Coord oldGravityCalc(Particle* from, Particle* to);
        Coord gravityCalc(Particle* particle);

        // visual graphic for debug
        void printAllSectors();
        
        Node(Dimension dimension);
        Node();
};