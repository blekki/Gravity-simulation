#include "cloud2d.h"

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