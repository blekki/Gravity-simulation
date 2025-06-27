#include "stdlib.h"
#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "enums.h"
#include "camera.h"
#include "cloud.h"

using namespace std;

// needy data
const uint WIDTH = 1024;
const uint HEIGHT = 720;
bool sim_pause = true;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) { // call actions
    // right now no one key callback exists
    if (key == GLFW_KEY_SPACE && action == 1)
        sim_pause = (sim_pause) ? false : true;
    
    if (key == GLFW_KEY_ESCAPE && action == 1)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // srand(time(0)); // todo: uncomment
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
    glEnable(GL_BLEND);

    Camera camera(WIDTH, HEIGHT);
    camera.updateMat();

    Cloud cloud(DIMENSION_3D);
    cloud.newParticles();
    cloud.print();
    glfwSwapBuffers(window);

    // basic loop
    while (!glfwWindowShouldClose(window)) {
        if (!sim_pause) {
            glViewport(0, 0, WIDTH, HEIGHT); // resize window
            
            // camera.rotate();
            
            
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear scene

            // print particles
            cloud.updateParticles();
            cloud.print();

            // other
            glfwSwapBuffers(window);
        }
        glfwPollEvents();
    }

    // before exit 
    glfwDestroyWindow(window);
}