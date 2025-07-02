#include "iostream"
#include "functional"
#include <GL/gl.h>

#include "cloud.h"

void Cloud::newParticles() {
    
    // for (uint i = 0; i < PARTICLE_COUNT; i++) {
    //     for 
    // }

    switch (dimension) {
        case DIMENSION_2D: newParticles2d(); break;
        case DIMENSION_3D: newParticles3d(); break;
        default: break;
    }
}

void Cloud::newParticles2d() {
    for (uint i = 0; i < PARTICLE_COUNT; i++) {
        // position in the space
        float x = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        float y = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        xyz_t pos(x, y, 0);

        // possibility generate particle speed
        float sx = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;
        float sy = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;

        xyz_t speed(sx, sy, 0);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::newParticles3d() {
    for (uint i = 0; i < PARTICLE_COUNT; i++) {
        // position in the space
        float x = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        float y = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        float z = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        xyz_t pos(x, y, z);

        // possibility generate particle speed
        float sx = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;
        float sy = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;

        xyz_t speed(sx, sy, 0);
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

// void Cloud::print() {
//     glPointSize(POINT_WIDTH);
//     glColor3f(1.0f, 1.0f, 1.0f);
//     glBegin(GL_POINTS);
//     switch (dimension) {
//         case DIMENSION_2D: print2d(); break;
//         case DIMENSION_3D: print3d(); break;
//         default: break;
//     }
//     glEnd();
// }

// void Cloud::print2d() {
//     for (uint i = 0; i < particles.size(); i++) {
//         // space into window coord
//         float x = particles[i].getX() / (SPACE_SIZE * 1.0f);
//         float y = particles[i].getY() / (SPACE_SIZE * 1.0f);
//         glVertex2f(x, y);
//     }
// }

// void Cloud::print3d() {
//     for (uint i = 0; i < particles.size(); i++) {
//         // space into window coord
//         float x = particles[i].getX() / (SPACE_SIZE * 1.0f);
//         float y = particles[i].getY() / (SPACE_SIZE * 1.0f);
//         float z = particles[i].getZ() / (SPACE_SIZE * 1.0f);
//         glVertex3f(x, y, z);
//     }
// }