#include "particle.h"
#include "math.h"

#include "iostream"

// init static parameters
const float Particle::DEFAULT_MASS = 10E3;
const int Particle::GENERATION_ACCURACY = 10000; // ps: highter number = less discretization of generate values

// private methods
void Particle::resetPos() { this->pos = Coord(0, 0, 0); }
void Particle::resetSpeed() { this->speedVec = Coord(0, 0, 0); }
void Particle::setDefaultMass() { this->mass = DEFAULT_MASS; }

// public methods
void Particle::setPos(Coord pos) { this->pos = pos; }

void Particle::setRandomPosXY(float range) {
    int radius = GENERATION_ACCURACY;
    int diameter = radius * 2;

    // generate value from -1.0f to 1.0f
    float x = (rand() % diameter - radius) / float(radius);
    float y = (rand() % diameter - radius) / float(radius);
    // convert into space coord
    pos.x = x * range;
    pos.y = y * range;
}

void Particle::setRandomPosXYZ(float range) {
    int radius = GENERATION_ACCURACY;
    int diameter = radius * 2;

    setRandomPosXY(range);
    float z = (rand() % diameter - radius) / float(radius); // generate value from -1.0f to 1.0f
    pos.z = z * range;  // convert into space coord
}

void Particle::updatePos() { this->pos += speedVec; }
void Particle::setSpeed(Coord speedVec) { this->speedVec = speedVec; }
void Particle::addSpeed(Coord speedVec) { this->speedVec += speedVec; }

float Particle::getX() { return pos.x; }
float Particle::getY() { return pos.y; }
float Particle::getZ() { return pos.z; }
Coord Particle::getPos() { return pos; }
Coord Particle::getSpeed() { return speedVec; }
float Particle::getMass() { return mass; }

// constructor
Particle::Particle() {
    resetPos();
    resetSpeed();
    setDefaultMass();
}

Particle::Particle(Coord pos, Coord speedVec)
: pos(pos), speedVec(speedVec), mass(DEFAULT_MASS) // weight of small asteroid in tonns
{}

Particle::Particle(Coord pos, Coord speedVec, float mass)
: pos(pos), speedVec(speedVec), mass(mass)
{}