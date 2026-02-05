#pragma once

#include "stdlib.h"
#include "ctime"

using namespace std;

class Timer
{
    private:
        clock_t timeBegin, timeEnd;
        float allTime;          // todo: remove
        uint frame;
        uint maxFrame;

        // todo: use this variables
        // uint currentFrame;
        // uint maxFrameRuntime;   // for debug mode

    public:
        void setMaxFrameCount(uint maxFrame);

        void start();
        void stop();
        bool isFrameOutOfRange();
        void reset();
        void printResults();

        Timer();
};