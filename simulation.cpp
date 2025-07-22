#include "stdlib.h"
#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "enums.h"
#include "window.h"
#include "camera.h"
#include "cloud2d.h"
#include "cloud3d.h"

using namespace std;

int main() {
    // make each simulation randomly
    // srand(time(0)); // todo: uncomment

    // glfw initialization
    if (!glfwInit()) {
        cout << "Initialization failed" << endl;
        exit(EXIT_FAILURE);
    }

    // view window initialization
    Window window;

    // preparation to simulation. First frame
    Camera camera(window.getWidth(), window.getHeight());
    camera.updateMatrix();

    Cloud3d cloud; //todo: make it as CloudFactory
    cloud.newParticles();
    cloud.print();
    window.swapBuffers();

    // in time frames rendering
    while (!window.windowShouldClose()) {
        window.preparationBeforeNextFrame();

        // all actions for changing the simulation stay
        if (!window.isSimulationOnPause()) {
            camera.rotate();
            cloud.updateParticles();
        }
        // todo: make possibility freeze simulation, but keep camera moves (so cool effect)

        // frame render
        cloud.print();
        window.swapBuffers();

        // other needy manipulation
        window.pollEvents();
    }
}