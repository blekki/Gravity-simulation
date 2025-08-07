#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

void Cloud::setDrawingProp() {
    glPointSize(POINT_WIDTH);
    glColor3fv(POINT_COLOR);
}

void Cloud::addNewParticle(Coord position, Coord speed) {
    particles.push_back(Particle(position, speed));
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

void Cloud::printNodeSectors() {
    node->printAllSectors();
}