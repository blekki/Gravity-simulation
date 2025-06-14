#include "xyz_t.h"

using namespace std;

class Particle
{
    private:
        xyz_t pos;
        xyz_t speed;
    
    public:
        void setPos(xyz_t pos);
        void setSpeed(xyz_t speed);

        float getX();
        float getY();

        void updatePos();

        Particle(xyz_t pos, xyz_t speed) 
        : pos(pos), speed(speed)
        {}
};