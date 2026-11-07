#include <stdlib.h>
#include <iostream>
#include <csignal>
#include <atomic>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "sim_engine.h"

SimEngine simEngine;

void signalHandler(int signal) {
    switch (signal) {
        case SIGINT: std::clog << "\rInterrupt ";
            break;
        default: std::clog << "\rUnknown ";
            break;
    }
    std::clog << "signal is called\n";
    
    simEngine.terminate();
}

int main() {
    std::signal(SIGINT, signalHandler);
    // todo: uncomment
    // srand(time(0));  // make each simulation randomly

    try {
        simEngine.startSimulation();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    std::clog << "[log] An application was successfully closed\n";
}