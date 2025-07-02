#include "cloud3d.h"

void Cloud3d::print() {
    glPointSize(POINT_WIDTH);
    glColor3fv(POINT_COLOR);
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        // space into window coord
        float x = particles[i].getX() / (SPACE_SIZE * 1.0f);
        float y = particles[i].getY() / (SPACE_SIZE * 1.0f);
        float z = particles[i].getZ() / (SPACE_SIZE * 1.0f);
        glVertex3f(x, y, z);
    }
    glEnd();
}