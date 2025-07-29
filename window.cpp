#include "window.h"

// static members
bool Window::sim_pause = true;

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { // call actions
    if (key == GLFW_KEY_SPACE && action == 1)
        sim_pause = (sim_pause) ? false : true;
    
    if (key == GLFW_KEY_ESCAPE && action == 1)
        glfwSetWindowShouldClose(window, true);
}

// other methods
int Window::getWidth() { return width; }
int Window::getHeight() { return height; }

bool Window::shouldClose() { 
    return glfwWindowShouldClose(window); 
}

bool Window::isSimulationOnPause() { 
    return sim_pause; 
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