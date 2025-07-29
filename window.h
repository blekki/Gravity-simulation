#pragma once

#include "stdlib.h"
#include "iostream"
#include <GLFW/glfw3.h>

using namespace std;

class Window
{
    private:
        GLFWwindow* window;

        // size in pixels
        int width = 1024;
        int height = 720;

        // key callback
        static bool sim_pause;
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    public:
        int getWidth();
        int getHeight();
        bool shouldClose();
        bool isSimulationOnPause(); //todo: maybe rename "doesSimulationPause"
        
        void swapBuffers();
        void preparationBeforeNextFrame();
        void pollEvents();

        Window();
        ~Window();
};