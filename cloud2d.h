#pragma once

#include "cloud.h"

class Cloud2d: public Cloud
{
    public:
        void print();
        void printNodeSectors();

        Cloud2d() : Cloud(DIMENSION_2D) {
            this->nodeSizeFromCenter = Coord(SPACE_SIZE, SPACE_SIZE, 0.0f);
        }
};