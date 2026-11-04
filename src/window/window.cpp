#include "window.h"

#include <iostream>

// static members
bool SimParams::pause_all = false;
bool SimParams::pause_gravity = false;
bool SimParams::rotate_camera = false;

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { // call actions
    // silence unused parameter warnings
    (void)scancode;
    (void)mods;

    // exit program
    if (key == GLFW_KEY_ESCAPE && action == 1)
        glfwSetWindowShouldClose(window, true);
        
    // off/on simulation params
    if (key == GLFW_KEY_SPACE && action == 1)
        SimParams::pause_all = !SimParams::pause_all;
    if (key == GLFW_KEY_P && action == 1)
        SimParams::pause_gravity = !SimParams::pause_gravity;
    if (key == GLFW_KEY_C && action == 1)
        SimParams::rotate_camera = !SimParams::rotate_camera;
}

// other methods
int Window::getWidth() { return width; }
int Window::getHeight() { return height; }

bool Window::shouldClose() { 
    return glfwWindowShouldClose(window); 
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::prepareToNextFrame() {
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height); // resize window
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear scene

    camera.setAspect(width, height);
    camera.updateMatrix();
    if (SimParams::rotate_camera && !SimParams::pause_all) {
        camera.rotate();
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::capFrameRate() {
    volatile double currentTime = glfwGetTime();
    while ((currentTime - prevFrameTime) < (1.0 / FPS_LOCK)) {
        currentTime = glfwGetTime();
        pollEvents();
    }
    prevFrameTime = currentTime;
}

void Window::init() {
    window = glfwCreateWindow(width, height, "Space simulation", NULL, NULL);
    if (!window) {
        throw std::runtime_error("Window context creation failed");
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

Window::Window() {};

Window::Window(int width, int height) : width(width), height(height) {
    Window();
}

Window::~Window() {
    glfwDestroyWindow(window);
}