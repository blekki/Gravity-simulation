#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

void Cloud::newParticles() {
    for (uint p = 0; p < PARTICLE_COUNT; p++) {
        xyz_t pos(0, 0, 0);
        for (uint axis = 0; axis < dimension; axis++) {
            float value = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
            pos.setAxis(axis, value);
        }

        xyz_t speed(0, 0, 0);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::updateParticles() {
    this->node = make_unique<Node>(dimension);
    this->node->setParentFieldSize(xyz_t(-SPACE_SIZE, -SPACE_SIZE, -SPACE_SIZE), xyz_t(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE));
    this->node->split(particles);
    
    for (uint i = 0; i < particles.size(); i++) {
        xyz_t vec = node->gravityInf(&particles[i]);
        particles[i].addSpeed(vec);
        particles[i].updatePos();
    }
}