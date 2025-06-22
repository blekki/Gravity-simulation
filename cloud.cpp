#include "iostream"
#include "functional"

#include "cloud.h"
#include "massPoint.h"

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

void Cloud::printsq(xyz_t pos1, xyz_t pos2) {
    pos1 = pos1 / (VALUE_RANGE * 1.0f);
    pos2 = pos2 / (VALUE_RANGE * 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(pos1.x, pos1.y);
    glVertex2f(pos1.x, pos2.y);
    glVertex2f(pos2.x, pos2.y);
    glVertex2f(pos2.x, pos1.y);
    glVertex2f(pos1.x, pos1.y);
    glEnd();
}

void Cloud::updatePos() {
    this->node = make_unique<Node>(0);
    this->node->setCanvasSize(xyz_t(-VALUE_RANGE, -VALUE_RANGE, 0), xyz_t(VALUE_RANGE, VALUE_RANGE, 0));
    this->node->split(particles);

    for (uint i = 0; i < particles.size(); i++) {
        // cout << i << endl;
    // {uint i = 0;
        // if (i == 0) {
            xyz_t vec = node->gravityVec(&particles[i]);
            particles[i].addSpeed(vec);
            // cout << vec.x << " : " << vec.y << endl;
            particles[i].updatePos();
        // }
    }

    // {uint i = 0;
    //     xyz_t vec(0, 0, 0);
    //     vec = node->gravityVec(&particles[i]);
    //     // if (isnan(vec.x) || isnan(vec.y)) {
    //     //     cout << particles[i].count << endl;
    //     //     cout << particles[i].getX() << " : " << particles[i].getY() << endl;
    //     //     cout << vec.x << " : " << vec.y << endl;
    //         // exit(0);
    //     // }
    //     // particles[i].addSpeed(vec);
    //     particles[i].addSpeed(node->gravityVec(&particles[i]));
    //     particles[i].updatePos();
    // }


    // for (uint i = 0; i < particles.size(); i++) {
    //     xyz_t sum(0, 0, 0);
    //     for (uint b = 0; b < particles.size(); b++) {
    //         if (i != b)
    //             sum += node->gravityVec2(&particles[i], &particles[b]);
    //     }
    //     particles[i].addSpeed(sum);
    //     particles[i].updatePos();
    // }
}

void Cloud::print() {
    glPointSize(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {

        float x = particles[i].getX() / (VALUE_RANGE * 1.0f);
        float y = particles[i].getY() / (VALUE_RANGE * 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}