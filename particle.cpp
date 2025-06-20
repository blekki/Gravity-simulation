#include "particle.h"

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

void Particle::updatePos() {
    pos += speed;
}