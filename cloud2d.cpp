#include "cloud2d.h"

void Cloud2d::print() {
    glPointSize(POINT_WIDTH);
    glColor3fv(POINT_COLOR);
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {
        // space into window coord
        float x = particles[i].getX() / (SPACE_SIZE * 1.0f);
        float y = particles[i].getY() / (SPACE_SIZE * 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}