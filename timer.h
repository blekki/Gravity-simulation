#pragma once

#include "stdlib.h"
#include "ctime"

using namespace std;

class Timer
{
    private:
        clock_t timeBegin, timeEnd;
        float allTime;
        uint frame;
        uint maxFrame;

    public:
        void setMaxFrameCount(uint maxFrame);

        void start();
        void stop();
        bool isFrameOutOfRange();
        void reset();
        void printResults();

        Timer();
};