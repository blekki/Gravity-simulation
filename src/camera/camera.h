#pragma once

#include <GL/glu.h>

class Camera
{
    private:
        float fovy = 60.0f;
        float aspect = 1024.0f / 720.0f;
        float zNear = 0.1f;
        float zFar = 1000.0f;

        float angle = 0.0f; // todo: rename

    public:
        void setAspect(int width, int height) {
            aspect = (float)width / (float)height;
        }

        void updateMatrix() {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(fovy, aspect, zNear, zFar);
            
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -2);
            glRotatef(angle, 0, 1, 0);
        }
        
        void rotate() {
            angle += 0.2f;
            if (angle > 360.0f)
                angle -= 360.0f;
        }
};