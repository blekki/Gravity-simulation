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

        int width = 1024;   // canvas size in pixel
        int height = 720;   //
        const char* title = "Window";
        bool isInitialized = false;

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

        void init(int width, int height, const char* title);

        ~Window();
};