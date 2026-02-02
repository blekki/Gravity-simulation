#pragma once

using namespace std;

class ICloud
{
    public:
        virtual void newParticles() = 0;
        virtual void updateParticles() = 0;
        virtual void print() = 0;
        // for debug
        virtual void printNodeSectors() = 0;

        ICloud(){};
};