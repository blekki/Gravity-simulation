#pragma once

struct xyz_t
{
    float x;
    float y;
    float z;

    void normalize();
    void offset();
    
    void operator+=(xyz_t other);
    xyz_t operator+(xyz_t other);
    xyz_t operator-(xyz_t other);
    xyz_t operator*(xyz_t other);
    xyz_t operator+(float num); // very specific action
    xyz_t operator-(float num); // very specific action
    xyz_t operator/(float num);
    xyz_t operator*(float num);

    xyz_t(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    xyz_t(){}
};