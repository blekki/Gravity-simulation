#include "stdlib.h"
#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "enums.h"
#include "window.h"
#include "camera.h"
#include "cloud.h"
// #include "ICloud.h"
// #include "cloudFactory.h"
#include "timer.h"

using namespace std;

int main() {
    // make each simulation randomly
    // srand(time(0)); // todo: uncomment

    // glfw initialization
    if (!glfwInit()) {
        cerr << "Initialization failed" << endl;
        exit(EXIT_FAILURE);
    }

    // view window initialization
    Window window;

    // preparation to simulation. Load matrices
    Camera camera(window.getWidth(), window.getHeight());
    camera.updateMatrix();
    
    // create cloud with particles
    Cloud cloud(DIMENSION_3D);

    // actually a timer
    Timer timer;
    timer.setMaxFrameCount(200);
    
    // render preview frame
    cloud.print();
    window.swapBuffers();

    // in time frames rendering
    while (!window.shouldClose() && !timer.isFrameOutOfRange()) {
        timer.start();
        window.capFrameRate(); // fps lock
        window.preparationBeforeNextFrame();

        // all actions for changing the simulation stay
        if (!window.isSimulationOnPause()) {
            if (window.isCameraRotate())
                camera.rotate();
            if (window.isPartilesSimulate())
                cloud.updateParticles();
        }

        // frame render
        // cloud.printNodeSectors();
        cloud.print();
        window.swapBuffers();

        // other needy manipulation
        window.pollEvents();
        timer.stop();
    }
    timer.printResults();

    clog << "[log] An application was successfully closed" << endl;
}