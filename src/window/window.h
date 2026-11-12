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

    public:
        ~Window();
        void init(int width, int height, const char* title);
        
        int getWidth();
        int getHeight();

        bool shouldClose();
        void prepareToNextFrame();
        void swapBuffers();
        void pollEvents();
};