#pragma once

struct xyz_t
{
    float x;
    float y;
    float z;

    void operator+=(xyz_t other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }

    xyz_t operator+(xyz_t other) {
        xyz_t current;
        current.x = this->x + other.x;
        current.y = this->y + other.y;
        current.z = this->z + other.z;
        return current;
    }

    xyz_t operator-(xyz_t other) {
        xyz_t current;
        current.x = this->x - other.x;
        current.y = this->y - other.y;
        current.z = this->z - other.z;
        return current;
    }

    xyz_t operator/(float num) {
        xyz_t current;
        current.x = this->x / num;
        current.y = this->y / num;
        current.z = this->z / num;
        return current;
    }

    xyz_t(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    xyz_t(){}
};