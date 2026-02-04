#include "iostream"
#include <GL/gl.h>

#include "cloud.h"

// private methods
void Cloud::newParticles() {
    switch (this->dimension) {
    case DIMENSION_2D:
        for (uint i = 0; i < PARTICLE_COUNT; i++) {
            Particle unit;
            unit.setRandomPosXY(SPACE_SIZE);
            addNewParticle(unit);
        };
    break;
    case DIMENSION_3D: 
        for (uint i = 0; i < PARTICLE_COUNT; i++) {
            Particle unit;
            unit.setRandomPosXYZ(SPACE_SIZE);
            addNewParticle(unit);
        };
    break;
    default: break;
    }
}

void Cloud::addNewParticle(Particle particle) {
    particles.push_back(particle);
}

void Cloud::addNewParticle(Coord position, Coord speed) {
    particles.push_back(Particle(position, speed));
}

void Cloud::setDrawingProp() {
    glPointSize(POINT_WIDTH);
    glColor3fv(POINT_COLOR);
}

Coord Cloud::asNDC(Coord coord) {
    Coord ndcCoord = coord / SPACE_SIZE;
    return ndcCoord;
}

// public methods
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

void Cloud::print() {
    setDrawingProp();
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        Coord pos = asNDC(particles[i].getPos());   // convert coord into from -1.0 to 1.0
        glVertex3f(pos.x, pos.y, pos.z);
    }
    glEnd();
}

void Cloud::printNodeSectors() {
    node->printAllSectors();
}

// constructor
Cloud::Cloud(Dimension dimension) : dimension(dimension) {
    newParticles();

    switch (dimension) {
    case DIMENSION_2D:
        nodeSizeFromCenter = Coord(SPACE_SIZE, SPACE_SIZE, 0.0f);
        break;
    case DIMENSION_3D:
        nodeSizeFromCenter = Coord(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);
        break;
    default: break;
    }
}