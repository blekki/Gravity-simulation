#include "window.h"

// static members
bool Window::sim_pause = false;
bool Window::rotate_camera = false;
bool Window::sim_particles = true;

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { // call actions
    // exit program
    if (key == GLFW_KEY_ESCAPE && action == 1)
        glfwSetWindowShouldClose(window, true);
        
    // off/on all frame changing
    if (key == GLFW_KEY_SPACE && action == 1) 
        sim_pause = (sim_pause) ? false : true;
    // off/on camera rotation
    if (key == GLFW_KEY_C && action == 1)
        rotate_camera = (rotate_camera) ? false : true;
    // off/on particle simulation
    if (key == GLFW_KEY_P && action == 1)
        sim_particles = (sim_particles) ? false : true;
}

// other methods
int Window::getWidth() { return width; }
int Window::getHeight() { return height; }
bool Window::isSimulationOnPause() { return sim_pause; }
bool Window::isCameraRotate() { return rotate_camera; }
bool Window::isPartilesSimulate() { return sim_particles; }

bool Window::shouldClose() { 
    return glfwWindowShouldClose(window); 
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::preparationBeforeNextFrame() {
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height); // resize window
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear scene
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

Window::Window() {
    // window initialization
    window = glfwCreateWindow(width, height, "Space simulation", NULL, NULL);
    if (!window) {
        cout << "Window context creation failed" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

Window::~Window() {
    glfwDestroyWindow(window);
}