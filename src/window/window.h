#pragma once

#include "stdlib.h"
#include "iostream"
#include <GLFW/glfw3.h>

using namespace std;

class Window
{
    private:
        GLFWwindow* window;

        // canvas size in pixel
        int width = 1024;
        int height = 720;

        // key callback
        static bool sim_pause;
        static bool rotate_camera;
        static bool sim_particles;
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

        // fps lock feature
        double prevFrameTime = 0.0f;
        const double FPS_LOCK = 120.0;

    public:
        int getWidth();
        int getHeight();
        bool shouldClose();
        bool isSimulationOnPause();
        bool isCameraRotate();
        bool isPartilesSimulate();
        
        void swapBuffers();
        void preparationBeforeNextFrame();
        void pollEvents();
        void capFrameRate();    // wait until the frame time comes

        Window();
        ~Window();
};