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