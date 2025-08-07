#include "stdlib.h"
#include "iostream"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "enums.h"
#include "window.h"
#include "camera.h"
#include "ICloud.h"
#include "cloudFactory.h"

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

    // preparation to simulation. Load matrices
    Camera camera(window.getWidth(), window.getHeight());
    camera.updateMatrix();
    
    // create cloud with particles
    CloudFactory cloudFactory;
    ICloud* cloud = cloudFactory.createCloud(DIMENSION_2D); //todo: make it as CloudFactory
    cloud->newParticles();
    
    // render preview frame
    cloud->print();
    window.swapBuffers();

    // for debug
    clock_t oldTime, newTime;
    float allTime = 0.0f;
    float avarageTime = 0.0f;
    const uint FRAMES_COUNT = 200;
    uint frames = 0;

    // in time frames rendering
    while (!window.shouldClose() && frames < FRAMES_COUNT) {
        window.preparationBeforeNextFrame();

        oldTime = clock();
        // all actions for changing the simulation stay
        if (!window.isSimulationOnPause()) {
            if (window.isCameraRotate())
                camera.rotate();
            if (window.isPartilesSimulate())
                cloud->updateParticles();
        }
        newTime = clock();
        double delta = double(newTime - oldTime) / double(CLOCKS_PER_SEC);
        // cout << "Time: " << delta << " sec" << endl;
        allTime += delta;
        frames++;

        // frame render
        // cloud->printNodeSectors();
        cloud->print();
        window.swapBuffers();

        // other needy manipulation
        window.pollEvents();
    }
    // cout << endl;
    avarageTime = allTime / float(frames);
    cout << "frames: " << frames << endl;
    cout << "allTime: " << allTime << endl;
    cout << "avarageTime: " << avarageTime << endl;

    // delete unneeded
    cloud = nullptr;
    delete cloud;
}