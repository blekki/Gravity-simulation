#include "timer.h"
#include "iostream"

// set
void Timer::setMaxFrameCount(uint maxFrame) {
    this->maxFrame = maxFrame;
}

// other methods
void Timer::start() {
    frame++;
    timeBegin = clock();
}

void Timer::stop() {
    timeEnd = clock();
    float delta = float(timeEnd - timeBegin) / float(CLOCKS_PER_SEC);
    allTime += delta;
}

bool Timer::isFrameOutOfRange() {
    return (frame > maxFrame) ? true : false;
}

void Timer::reset() {
    allTime = 0.0f;
    frame = 0;
    maxFrame = 200;
}

void Timer::printResults() {
    float avarageTime = allTime / float(frame);
    float fps = 1.0f / avarageTime;
    cout << "frame count: " << frame << endl;
    cout << "run (sec): " << allTime << endl;
    cout << "avarage frame time consuming: " << avarageTime << endl;
    cout << "fps: " << fps << endl;
}

Timer::Timer() {
    reset();
};