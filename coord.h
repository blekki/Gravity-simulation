#pragma once
#include "stdlib.h"

struct Coord
{
    float x;
    float y;
    float z;

    void normalize();
    void axesPermutation(); // todo: rename from offset
    double diagonaleSq(); // prefix "Sq" because it doesn't use sqrt() inside
    float getAxis(uint index); //todo: axis --> getAxis
    void setAxis(uint index, float value);

    Coord addToEveryAxes(float value); // todo: need update
    void operator+=(Coord other);
    Coord operator+(Coord other);
    Coord operator-(Coord other);
    Coord operator*(Coord other);
    Coord operator/(float num);
    Coord operator*(float num);

    // todo: some change
    // Coord operator+(float num); // very specific action
    // Coord operator-(float num); // very specific action

    Coord(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    Coord(){}
};