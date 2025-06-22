#include "particle.h"
#include "math.h"

#include "iostream"

void Particle::setPos(xyz_t pos) {
    this->pos = pos;
}

void Particle::setSpeed(xyz_t speed) {
    this->speed = speed;
}

void Particle::addSpeed(xyz_t speed) {
    this->speed += speed;
}

float Particle::getX() { return pos.x; }
float Particle::getY() { return pos.y; }
xyz_t Particle::getXYZ() { return pos; }
xyz_t Particle::getSpeed() { return speed; }
float Particle::getMass() {return mass; }

void Particle::updatePos() {
    pos += speed;
}