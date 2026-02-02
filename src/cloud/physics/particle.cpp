#include "particle.h"
#include "math.h"

#include "iostream"

void Particle::setPos(Coord pos) { this->pos = pos; }
void Particle::setSpeed(Coord speedVec) { this->speedVec = speedVec; }
void Particle::addSpeed(Coord speedVec) { this->speedVec += speedVec; }

float Particle::getX() { return pos.x; }
float Particle::getY() { return pos.y; }
float Particle::getZ() { return pos.z; }
Coord Particle::getPos() { return pos; }
Coord Particle::getSpeed() { return speedVec; }
float Particle::getMass() {return mass; }

void Particle::updatePos() {
    pos += speedVec;
}