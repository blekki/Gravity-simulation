#include "cloud2d.h"

void Cloud2d::newParticles() {
    for (uint p = 0; p < PARTICLE_COUNT; p++) {
        // position
        float x = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        float y = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        Coord position(x, y, 0.0f);

        // speed
        Coord speed(0.0f, 0.0f, 0.0f);
        
        // create new particle
        addNewParticle(position, speed);
    }
}

void Cloud2d::print() {
    setDrawingProp();
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        // space into window coord
        float x = particles[i].getX() / (float) SPACE_SIZE;
        float y = particles[i].getY() / (float) SPACE_SIZE;
        glVertex2f(x, y);
    }
    glEnd();
}