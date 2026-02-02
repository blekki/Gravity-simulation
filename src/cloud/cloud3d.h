#pragma once

#include "cloud.h"

class Cloud3d: public Cloud
{
    public:
        virtual void newParticles() override;
        virtual void print() override;

        Cloud3d() : Cloud(DIMENSION_3D) {
            this->nodeSizeFromCenter = Coord(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);
        }
};