#pragma once
#include "xyz_t.h"

struct MassPoint
{
    xyz_t pos;
    int mass;

    MassPoint(){}
    MassPoint(xyz_t pos, int mass)
    : pos(pos), mass(mass)
    {}
};