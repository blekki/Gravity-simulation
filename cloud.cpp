#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

void Cloud::newParticles() {
    for (uint i = 0; i < PARTICLE_COUNT; i++) {
        // position in the space
        float x = rand() % VALUE_RANGE * 2.0f - VALUE_RANGE;
        float y = rand() % VALUE_RANGE * 2.0f - VALUE_RANGE;
        xyz_t pos(x, y, 0);

        float sx = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;
        float sy = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;

        xyz_t speed(sx, sy, 0);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::updateParticles() {
    this->node = make_unique<Node>();
    this->node->setParentFieldSize(xyz_t(-VALUE_RANGE, -VALUE_RANGE, 0), xyz_t(VALUE_RANGE, VALUE_RANGE, 0));
    this->node->split(particles);

    for (uint i = 0; i < particles.size(); i++) {
            xyz_t vec = node->gravityInf(&particles[i]);
            particles[i].addSpeed(vec);
            particles[i].updatePos();
    }
}

void Cloud::print() {
    glPointSize(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        // space into window coord
        float x = particles[i].getX() / (VALUE_RANGE * 1.0f);
        float y = particles[i].getY() / (VALUE_RANGE * 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}