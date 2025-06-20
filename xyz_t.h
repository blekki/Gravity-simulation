#pragma once

struct xyz_t
{
    float x;
    float y;
    float z;

    void normalize() {
        xyz_t k(1, 1, 1);
        xyz_t current;
        current.x = k.x / this->x;
        current.y = k.y / this->y;
        current.z = k.z / this->z;

        this->x = this->x * current.x;
        this->y = this->y * current.y;
        this->z = this->z * current.z;
    }

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

    xyz_t operator*(xyz_t other) {
        xyz_t current;
        current.x = this->x * other.x;
        current.y = this->y * other.y;
        current.z = this->z * other.z;
        return current;
    }

    xyz_t operator/(float num) {
        xyz_t current;
        current.x = this->x / num;
        current.y = this->y / num;
        current.z = this->z / num;
        return current;
    }

    xyz_t operator*(float num) {
        xyz_t current;
        current.x = this->x * num;
        current.y = this->y * num;
        current.z = this->z * num;
        return current;
    }

    // float operator/(xyz_t other) {
    //     float num1 = (this->x*this->x) + (this->y*this->y) + (this->z*this->z);
    //     float num2 = (other.x*other.x) + (other.y*other.y) + (other.z*other.z);
    //     return (num1 < num2) ? true : false;
    // }

    xyz_t(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    xyz_t(){}
};