#include "cloud3d.h"

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