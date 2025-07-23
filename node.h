#pragma once

#include "stdlib.h"
#include <GL/gl.h>
#include "math.h"
#include "vector"
#include "memory"

#include "enums.h"
#include "particle.h"
#include "coord.h"

using namespace std;

class Node
{   
    private: // todo: sort variables
        Dimension   dimension;
        Coord       sizeFrom, sizeTo; // todo: maybe rename
        Particle    mass_centre;
        uint        nestedness; // current daughter node level
        
        unique_ptr<Node[]> daughterNodes; // daughter nodes = 4 (2d dimension) or 8 (3d dimension)
        uint daughterNodeCount;

        // todo: remove
        static long long int fistParrentFieldSize; // max particles position from centre
        static constexpr float SIMULATION_QUALITY_COEF = 1.0f; // calculation accuracy (node size / dist > coef)

    private:
        vector<pair<Coord, Coord>> division(); // todo: rename
        uint whatKindRegion(Particle* particle); // todo: rename whichRegion
        float splitSpace(vector<Particle> particles); // todo: rename split

        void printNodeSectors2d(Coord sizeFrom, Coord sizeTo); // todo: made only one node printer
        void printNodeSectors3d(Coord sizeFrom, Coord sizeTo);
        void printInfLine(Coord from, Coord to); // todo: rename into "printInfluenceLines"

        double distance(Coord from, Coord to); // todo: rename to "distance"
        Coord addToEveryAxes(Coord vec, float value);
        void setDaughterFieldSize(Coord sizeFrom, Coord sizeTo);

    public:
        void setFieldSize(Coord sizeFrom, Coord sizeTo);
        void split(vector<Particle> particles);

        Coord oldGravityCalc(Particle* from, Particle* to); // todo: rename
        Coord gravityCalc(Particle* particle); // todo: rename

        Node(Dimension dimension, uint nestedness)
        : dimension(dimension), nestedness(nestedness) 
        { daughterNodeCount = pow(2, (uint) dimension); }
        
        Node(Dimension dimension)
        : dimension(dimension), nestedness(0)
        { daughterNodeCount = pow(2, (uint) dimension); }

        Node(){ daughterNodeCount = pow(2, (uint) dimension); }
};