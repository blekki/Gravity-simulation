#pragma once

#include "cloud.h"

class Cloud2d: public Cloud
{
    public:
        void print();

        Cloud2d()
        : Cloud(DIMENSION_2D)
        {}
};