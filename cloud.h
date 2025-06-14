#include "stdlib.h"
#include "vector"
#include <GL/gl.h>

#include "particle.h"

using namespace std;

class Cloud
{
    private:
        vector<Particle> particles;
        
        // range where particles can be created
        const uint VALUE_RANGE = 1000000; // 1M km
    
    public:
        // range out a centre in positive and negative sides
        // void setRange(uint rangeX, uint rangeY) { // todo: remove
        //     this->rangeX = rangeX;
        //     this->rangeY = rangeY;
        // }

        void newParticles(uint count) {

            float x, y;
            for (uint i = 0; i < count; i++) {
                // position in the space
                x = (rand() % VALUE_RANGE * 2.0f - VALUE_RANGE);
                y = (rand() % VALUE_RANGE * 2.0f - VALUE_RANGE);
                xyz_t pos(x, y, 0);

                xyz_t speed(0, 0, 0);
                particles.push_back(Particle(pos, speed));
            }
        }

        void print() {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_POINTS);
            for (uint i = 0; i < particles.size(); i++) {

                float x = particles[i].getX() / (VALUE_RANGE * 1.0f);
                float y = particles[i].getY() / (VALUE_RANGE * 1.0f);
                glVertex2f(x, y);
            }
            glEnd();
        }

        Cloud() {
            this->rangeX = 0;
            this->rangeY = 0;
        }
};