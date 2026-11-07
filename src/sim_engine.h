#pragma once
#include <thread>
#include <atomic>

#include "window.h"
#include "cloud.h"
#include "tick_rate_control.h"

// #define DEBUG_MODE

class SimEngine
{
    private:
        Window window;
        std::unique_ptr<std::thread> physicsThread;
        TickRateControl processTickControl;
        TickRateControl physicsTickControl;

        bool isInitialized = false;
        bool isStarted = false;
        std::atomic<bool> shouldStop = false;
        
    private:
        void process() {
            // !!!!!!!!!!!
            // todo: split render and physics  

            Cloud cloud(DIMENSION_2D);
            // preview frame render
            window.prepareToNextFrame();
            cloud.print();
            window.swapBuffers();

            // realtime rendering
            while (!shouldStop.load(std::memory_order_acquire) && !window.shouldClose()) {
                processTickControl.frameStarted();
                window.prepareToNextFrame();

                // glBegin(GL_TRIANGLES);
                // glVertex2f(0.0, 0.0);
                // glVertex2f(0.0, 0.6);
                // glVertex2f(0.6, 0.6);
                // glEnd();

                if (!SimParams::pause_all) {
                    if (!SimParams::pause_gravity) {
                        float delta_time = 0.01f;   // todo: set real delta time
                        cloud.updateParticles(delta_time);
                    }
                }
            
                // frame render
                // cloud.printNodeSectors();
                cloud.print();
                
                window.swapBuffers();
                window.pollEvents();
                processTickControl.frameFinished();
            }
            std::clog << "----------\n";
            std::clog << "Process (render) logs:\n";
            processTickControl.printLogs();
        }

        void physics() {
            while (!shouldStop.load(std::memory_order_acquire) && !window.shouldClose()) {
                physicsTickControl.frameStarted();
                // calc all physics

                // todo: add functionality

                physicsTickControl.frameFinished();
            }
            std::clog << "----------\n";
            std::clog << "Process (physics) logs:\n";
            physicsTickControl.printLogs();
        }

    public:
        SimEngine(const SimEngine& other) = delete;
        SimEngine(SimEngine&& other) = delete;
        SimEngine() {
            processTickControl.setTickRate(0); // unlimited tickrate
            physicsTickControl.setTickRate(60);
        }

        ~SimEngine() {
            terminate();
            if (physicsThread->joinable())
                physicsThread->join();
        }

        void init() {
            if (isInitialized)
                return;
            window.init(1024, 720, "Gravity simulation");
            isInitialized = true;
            std::clog << "SimEngine initialized\n";
        }

        void startSimulation() {    // blocking method
            if (isStarted) 
                return;
            if (!isInitialized)
                init();
            isStarted = true;
            
            physicsThread = std::make_unique<std::thread>(&SimEngine::physics, this);
            process();

            if (physicsThread->joinable())
                physicsThread->join();
        }

        void terminate() {  // signal to stop all processes
            shouldStop.store(true, std::memory_order_release);
        }
};