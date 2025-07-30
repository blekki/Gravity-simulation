#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

void Cloud::setDrawingProp() {
    glPointSize(POINT_WIDTH);
    glColor3fv(POINT_COLOR);
}

void Cloud::newParticles() {
    for (uint p = 0; p < PARTICLE_COUNT; p++) {
        // position
        Coord pos(0.0f, 0.0f, 0.0f);
        for (uint axis = 0; axis < dimension; axis++) {
            float value = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
            pos.setAxis(axis, value);
        }
        // speed
        Coord speed(0.0f, 0.0f, 0.0f);
        
        // push
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::updateParticles() {
    node = make_unique<Node>(dimension);
    node->setField(nodeSizeFromCenter * -1.0f, nodeSizeFromCenter);
    node->splitter(particles);
    
    for (uint i = 0; i < particles.size(); i++) {
        Coord vec = node->gravityCalc(&particles[i]);
        particles[i].addSpeed(vec);
        particles[i].updatePos();
    }
}