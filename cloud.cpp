#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

void Cloud::newParticles() {
    for (uint p = 0; p < PARTICLE_COUNT; p++) {
        Coord pos(0, 0, 0);
        for (uint axis = 0; axis < dimension; axis++) {
            float value = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
            pos.setAxis(axis, value);
        }

        Coord speed(0, 0, 0);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::updateParticles() {
    this->node = make_unique<Node>(dimension);
    // todo: make field size from class variables. Not inizialize it here
    this->node->setField(Coord(-SPACE_SIZE, -SPACE_SIZE, -SPACE_SIZE), Coord(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE));
    this->node->splitter(particles);
    
    for (uint i = 0; i < particles.size(); i++) {
        Coord vec = node->gravityCalc(&particles[i]);
        particles[i].addSpeed(vec);
        particles[i].updatePos();
    }

    // author comment: perspective position for printing debug grids 
}