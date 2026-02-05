#include "coord.h"
#include "math.h"

void Coord::normalize() {
    
    double sqLen = diagonaleSq();
    if (sqLen != 0.0f) {
        float coef = 1.0f / sqrt(sqLen);
        x = x * coef;
        y = y * coef;
        z = z * coef;
    }
    else {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
         
}

void Coord::axesPermutation() {
    float a = this->z;
    this->z = this->y;
    this->y = this->x;
    this->x = a;
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
// bool Coord::operator==(const Coord other) {
bool operator==(const Coord& lhs, const Coord& rhs) {
    if (lhs.x != rhs.x) return false;
    if (lhs.y != rhs.y) return false;
    if (lhs.z != rhs.z) return false;
    // else
    return true;
}

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