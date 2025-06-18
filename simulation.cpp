#include "stdlib.h"
#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "cloud.h"

using namespace std;

const uint WIDTH = 1024;
const uint HEIGHT = 720;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { // call actions
    // right now no one key callback exists
    return;
}

int main() {
    // srand(time(0));
    // glfw initialization
    if (!glfwInit()) {
        cout << "Initialization failed" << endl;
        exit(EXIT_FAILURE);
    }

    // window initialization
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Space simulation", NULL, NULL);
    if (!window) {
        cout << "Window context creation failed" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);


    Cloud cloud;
    cloud.newParticles();
    cloud.print();
    glfwSwapBuffers(window);

    // basic loop
    while (!glfwWindowShouldClose(window)) {
        glViewport(0, 0, WIDTH, HEIGHT); // resize window
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear scene

        // print particles
        cloud.updatePos();
        cloud.print();

        // break;

        // other
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // before exit 
    glfwDestroyWindow(window);
}