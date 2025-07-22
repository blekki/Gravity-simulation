#include "coord.h"
#include "math.h"

void Coord::normalize() {
    Coord k(1, 1, 1);
    Coord vec;
    vec.x = k.x / abs(this->x);
    vec.y = k.y / abs(this->y);
    vec.z = k.z / abs(this->z);

    this->x = this->x * vec.x;
    this->y = this->y * vec.y;
    this->z = this->z * vec.z;
}

void Coord::axesPermutation() {
    float a = this->x;
    this->x = this->y;
    this->y = this->z;
    this->z = a;
}

double Coord::diagonaleSq() {
    double diagonale =  (this->x*this->x) +
                        (this->y*this->y) + 
                        (this->z*this->z);
    return diagonale;
}

float Coord::getAxis(uint index) {
    switch (index) {
        case 0: return this->x; break;
        case 1: return this->y; break;
        case 2: return this->z; break;
        default: return NAN; break;
    }
}

void Coord::setAxis(uint index, float value) {
    switch (index) {
        case 0: this->x = value; break;
        case 1: this->y = value; break;
        case 2: this->z = value; break;
        default: break;
    }
}

// overload operators
void Coord::operator+=(Coord other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

Coord Coord::operator+(Coord other) {
    Coord current;
    current.x = this->x + other.x;
    current.y = this->y + other.y;
    current.z = this->z + other.z;
    return current;
}

Coord Coord::operator-(Coord other) {
    Coord current;
    current.x = this->x - other.x;
    current.y = this->y - other.y;
    current.z = this->z - other.z;
    return current;
}

Coord Coord::operator*(Coord other) {
    Coord current;
    current.x = this->x * other.x;
    current.y = this->y * other.y;
    current.z = this->z * other.z;
    return current;
}

// Coord Coord::operator+(float num) {
//     Coord result;
//     result.x = this->x + num;
//     result.y = this->y + num;
//     result.z = this->z + num;
//     return result;
// }

// Coord Coord::operator-(float num) {
//     Coord result;
//     result.x = this->x - num;
//     result.y = this->y - num;
//     result.z = this->z - num;
//     return result;
// }

Coord Coord::operator/(float num) {
    Coord current;
    current.x = this->x / num;
    current.y = this->y / num;
    current.z = this->z / num;
    return current;
}

Coord Coord::operator*(float num) {
    Coord current;
    current.x = this->x * num;
    current.y = this->y * num;
    current.z = this->z * num;
    return current;
}