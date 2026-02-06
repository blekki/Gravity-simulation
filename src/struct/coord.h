#pragma once
#include "stdlib.h"

struct Coord
{
    float x;
    float y;
    float z;

    void normalize();
    void axesPermutation();
    double diagonale();
    double diagonaleSq();       // gives you square diagonale
    float getAxis(uint index);
    void setAxis(uint index, float value);
    void addToEveryAxes(float value);

    friend bool operator==(const Coord& lhs, const Coord& rhs);
    friend bool operator!=(const Coord& lhs, const Coord& rhs);
    void operator+=(Coord other);
    Coord operator+(Coord other);
    Coord operator-(Coord other);
    Coord operator*(Coord other);
    Coord operator/(float num);
    Coord operator*(float num);

    Coord(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    Coord(){}
};