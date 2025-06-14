#include "xyz_t.h"

using namespace std;

class Particle
{
    private:
        xyz_t pos;
        xyz_t speed;
    
    public:
        void setPos(xyz_t pos) {
            this->pos = pos;
        }

        void setSpeed(xyz_t speed) {
            this->speed = speed;
        }

        float getX() { return pos.x; }
        float getY() { return pos.y; }

        Particle(xyz_t pos, xyz_t speed) 
        : pos(pos), speed(speed)
        {}
};