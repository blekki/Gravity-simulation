#include "cloud.h"

void Cloud::newParticles(uint count) {
    for (uint i = 0; i < count; i++) {
        // position in the space
        float x = rand() % VALUE_RANGE * 2.0f - VALUE_RANGE;
        float y = rand() % VALUE_RANGE * 2.0f - VALUE_RANGE;
        xyz_t pos(x, y, 0);

        float sx = rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;
        float sy = rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;

        xyz_t speed(sx, sy, 0);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::updatePos() {
    for (uint i = 0; i < particles.size(); i++) {
        particles[i].updatePos();
    }
}

void Cloud::print() {

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {

        float x = particles[i].getX() / (VALUE_RANGE * 1.0f);
        float y = particles[i].getY() / (VALUE_RANGE * 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}