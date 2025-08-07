#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

#include "ctime" // can be deleted

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
    
    // clock_t oldTime, newTime;
    // oldTime = clock();
    for (uint i = 0; i < particles.size(); i++) {
        Coord vec = node->gravityCalc(&particles[i]);
        particles[i].addSpeed(vec);
        particles[i].updatePos();
    }
    // newTime = clock();
    // double delta = double(newTime - oldTime) / double(CLOCKS_PER_SEC);
    // cout << "Time: " << delta << " sec" << endl;
}

void Cloud::printNodeSectors() {
    node->printAllSectors();
}