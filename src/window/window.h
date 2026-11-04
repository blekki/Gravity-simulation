#pragma once

#include <GLFW/glfw3.h>
#include "camera.h"

struct SimParams
{
    static bool pause_all;
    static bool pause_gravity;
    static bool rotate_camera;  // todo: rename like camera_spin_around
};

class Window
{
    private:
        GLFWwindow* window;
        Camera camera;

        // canvas size in pixel
        int width = 1024;
        int height = 720;

        // key callback
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

        // fps lock feature
        double prevFrameTime = 0.0f;
        const double FPS_LOCK = 120.0;

    public:
        int getWidth();
        int getHeight();
        bool shouldClose();
        
        void swapBuffers();
        void prepareToNextFrame();
        void pollEvents();
        void capFrameRate();    // wait until the frame time comes

        void init();

        Window();
        Window(int width, int height);
        ~Window();
};