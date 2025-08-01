#pragma once

#include "cloud.h"

class Cloud3d: public Cloud
{
    public:
        void print();

        Cloud3d() : Cloud(DIMENSION_3D) {
            this->nodeSizeFromCenter = Coord(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);
        }
};