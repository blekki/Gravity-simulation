#include "stdlib.h"
#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "enums.h"
#include "window.h"
#include "cloud.h"
#include "timer.h"


int main() {
    // srand(time(0));  // make each simulation randomly    // todo: uncomment

    Window window;
    try {
        window.init(1024, 720, "Gravity simulation");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // preparation to simulation. Load matrices
    // Camera camera(window.getWidth(), window.getHeight());
    // camera.updateMatrix();
    
    // create cloud with particles
    Cloud cloud(DIMENSION_2D);

    // actually a timer
    Timer timer;
    timer.setMaxFrameCount(200);
    
    // render preview frame
    cloud.print();
    window.swapBuffers();

    // in time frames rendering
    // while (!window.shouldClose() && !timer.isFrameOutOfRange()) {
    while (!window.shouldClose()) {
        timer.start();
        window.capFrameRate(); // fps lock
        window.prepareToNextFrame();

        // changing the simulation stay
        if (!SimParams::pause_all) {
            if (!SimParams::pause_gravity) {
                // todo: calc delta time
                float delta_time = 0.01f;
                cloud.updateParticles(delta_time);
            }
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

    std::clog << "[log] An application was successfully closed" << std::endl;
}