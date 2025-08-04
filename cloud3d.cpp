#include "cloud3d.h"

void Cloud3d::newParticles() {
    for (uint p = 0; p < PARTICLE_COUNT; p++) {
        // position
        float x = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        float y = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        float z = rand() % (SPACE_SIZE) * 2.0f - SPACE_SIZE;
        Coord position(x, y, z);
        
        // speed
        Coord speed(0.0f, 0.0f, 0.0f);

        // push
        addNewParticle(position, speed);
    }
}

void Cloud3d::print() {
    setDrawingProp();
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        // space into window coord
        float x = particles[i].getX() / (float) SPACE_SIZE;
        float y = particles[i].getY() / (float) SPACE_SIZE;
        float z = particles[i].getZ() / (float) SPACE_SIZE;
        glVertex3f(x, y, z);
    }
    glEnd();
}