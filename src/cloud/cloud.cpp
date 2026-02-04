#include "iostream"
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
        Coord attraction = node->gravityCalc(&particles[i]);
        particles[i].addSpeed(attraction);
        particles[i].updatePos();
    }
}

void Cloud::printNodeSectors() {
    node->printAllSectors();
}

// ##########################

void Cloud::newParticles() {
    switch (this->dimension) {
        case DIMENSION_2D:
            for (uint i = 0; i < PARTICLE_COUNT; i++) {
                Particle unit;
                unit.setRandomPosXY(SPACE_SIZE);
                particles.push_back(unit);
            };
        break;
        case DIMENSION_3D: 
            for (uint i = 0; i < PARTICLE_COUNT; i++) {
                Particle unit;
                unit.setRandomPosXYZ(SPACE_SIZE);
                particles.push_back(unit);
            };
        break;
        default: break;
    }
}

Coord Cloud::asNDC(Coord coord) {
    Coord ndcCoord = coord / SPACE_SIZE;
    return ndcCoord;
}

void Cloud::print() {
    setDrawingProp();
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        Coord pos = asNDC(particles[i].getPos());
        glVertex3f(pos.x, pos.y, pos.z);
    }
    glEnd();
}