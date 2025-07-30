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
        Coord pos(0.0f, 0.0f, 0.0f);
        for (uint axis = 0; axis < dimension; axis++) {
            float value = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
            pos.setAxis(axis, value);
        }
        
        // float coords[DIMENSION_MAX];
        // for (uint axis = 0; axis < dimension; axis++)
        //     coords[axis] = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        // for (uint other_axis = dimension; other_axis < DIMENSION_MAX; other_axis++)
        //     coords[other_axis] = 0.0f;
        
        // Coord pos(coords[0], coords[1], coords[2]);
        Coord speed(0.0f, 0.0f, 0.0f);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::updateParticles() {
    this->node = make_unique<Node>(dimension);
    this->node->setField(nodeSizeFromCenter * -1.0f, nodeSizeFromCenter);
    this->node->splitter(particles);
    
    for (uint i = 0; i < particles.size(); i++) {
        Coord vec = node->gravityCalc(&particles[i]);
        particles[i].addSpeed(vec);
        particles[i].updatePos();
    }

    // author comment: perspective position for printing debug grids
}