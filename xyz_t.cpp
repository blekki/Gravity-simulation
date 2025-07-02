#include "xyz_t.h"
#include "math.h"

void xyz_t::normalize() {
    xyz_t k(1, 1, 1);
    xyz_t vec;
    vec.x = k.x / abs(this->x);
    vec.y = k.y / abs(this->y);
    vec.z = k.z / abs(this->z);

    this->x = this->x * vec.x;
    this->y = this->y * vec.y;
    this->z = this->z * vec.z;
}

void xyz_t::offset() {
    float a = this->z;
    this->z = this->y;
    this->y = this->x;
    this->x = a;
}

float xyz_t::axis(uint index) {
    switch (index) {
        case 0: return this->x; break;
        case 1: return this->y; break;
        case 2: return this->z; break;
        default: return NAN; break;
    }
}

void xyz_t::setAxis(uint index, float value) {
    switch (index) {
        case 0: this->x = value; break;
        case 1: this->y = value; break;
        case 2: this->z = value; break;
        default: break;
    }
}

// overload operators
void xyz_t::operator+=(xyz_t other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

xyz_t xyz_t::operator+(xyz_t other) {
    xyz_t current;
    current.x = this->x + other.x;
    current.y = this->y + other.y;
    current.z = this->z + other.z;
    return current;
}

xyz_t xyz_t::operator-(xyz_t other) {
    xyz_t current;
    current.x = this->x - other.x;
    current.y = this->y - other.y;
    current.z = this->z - other.z;
    return current;
}

xyz_t xyz_t::operator*(xyz_t other) {
    xyz_t current;
    current.x = this->x * other.x;
    current.y = this->y * other.y;
    current.z = this->z * other.z;
    return current;
}

xyz_t xyz_t::operator+(float num) {
    xyz_t result;
    result.x = this->x + num;
    result.y = this->y + num;
    result.z = this->z + num;
    return result;
}

xyz_t xyz_t::operator-(float num) {
    xyz_t result;
    result.x = this->x - num;
    result.y = this->y - num;
    result.z = this->z - num;
    return result;
}

xyz_t xyz_t::operator/(float num) {
    xyz_t current;
    current.x = this->x / num;
    current.y = this->y / num;
    current.z = this->z / num;
    return current;
}

xyz_t xyz_t::operator*(float num) {
    xyz_t current;
    current.x = this->x * num;
    current.y = this->y * num;
    current.z = this->z * num;
    return current;
}