#pragma once

#include "stdlib.h"
#include <GL/glu.h>

class Camera
{
    private:
        uint width;
        uint height;

    public:
        void updateMat() {
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);

            glLoadIdentity();
            gluPerspective(65.0f, width / (float) height, 0.1f, 1000.0f);
            glMatrixMode(GL_MODELVIEW);
            
            glLoadIdentity();
            glTranslatef(0, 0, -2);
        }
        
        void rotate() {
            glRotatef(0.1, 0, 1, 0);
        }

        Camera(uint width, uint height)
        : width(width), height(height)
        {}

        Camera()
        : width(1024), height(720)
        {}
};