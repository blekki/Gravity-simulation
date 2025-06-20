#pragma once

#include "stdlib.h"
#include <GL/gl.h>
#include "vector"
#include "memory"
#include "math.h"

#include "particle.h"
#include "xyz_t.h"

#include "iostream" // todo: remove

using namespace std;

class Node
{
    private:
        // about field
        unique_ptr<Node> node[4];
        xyz_t x1y1;
        xyz_t x2y2;
        // other
        // uint particle_count = 0;
        uint level; // current nestedness level

        Particle mass_centre;

        static const uint NESTEDNESS = 8; // max level
        static constexpr float COEF = 3.0f; // coef of (size / dist)
        // static constexpr float PARTICLE_MASS = 1E10;

    public:
        void setCanvasSize(xyz_t x1y1, xyz_t x2y2) {
            this->x1y1 = x1y1;
            this->x2y2 = x2y2;
        }

        float distCube(xyz_t from, xyz_t to) {
            xyz_t dist = to - from;
            float result = (dist.x*dist.x) + (dist.y*dist.y);// + (dist.z*dist.z);
            return result;
        }

        xyz_t gravityVec(Particle* particle) { // todo: make parameter a pointer on particle
            // xyz_t centre = (x2y2 - x1y1) / 2 + x1y1;

            // canvas
            float s = sqrt(distCube(x2y2, x1y1)); // right now sq
            xyz_t centre = mass_centre.getXYZ();
            float r = sqrt(distCube(centre, particle->getXYZ())); // right now sq

            bool last_level = false;
            for (uint a = 0; a < 4; a++)
                if (!node[a])
                    last_level = true;

            xyz_t gravity_vec(0, 0, 0);
            if (r / s > COEF || last_level) {
                float G = 6.6742E-11;
                float gravity = (G * particle->getMass() * mass_centre.getMass()) / (r * r);

                xyz_t dist = centre - particle->getXYZ();
                float k = dist.x / dist.y;
                // if (k) k += 1E-3;
                gravity_vec = xyz_t(gravity * k, gravity / k, 0);
            }
            else {
                for (uint a = 0; a < 4; a++) {
                    if (node[a]) {
                        gravity_vec += node[a]->gravityVec(particle);
                    }
                }
            }

            return gravity_vec;
        }

        float split(vector<Particle> particles) {
            if (particles.size() == 0) { // space without particles
                mass_centre = Particle(xyz_t(0, 0, 0), xyz_t(0, 0, 0), 0.0f);
                return 0.0f;
            }
            if (particles.size() == 1) { // space with only one particle
                mass_centre = particles[0];
                return particles[0].getMass();
            } 

            // find where are particles
            vector<Particle> region[4];
            xyz_t node_size(x2y2 - x1y1); //todo: x1y1 --> x1y1z1
            for (uint a = 0; a < particles.size(); a++) {
                // inside what kind quad
                int kind = 5;
                kind = (particles[a].getX() > (node_size.x / 2 + x1y1.x)) ? (kind)     : (kind - 2);
                kind = (particles[a].getY() > (node_size.y / 2 + x1y1.y)) ? (kind - 1) : (kind - 2);
                
                // remember where particele stays
                switch (kind) {
                    case 1: region[0].push_back(particles[a]); break;
                    case 2: region[1].push_back(particles[a]); break;
                    case 3: region[2].push_back(particles[a]); break;
                    case 4: region[3].push_back(particles[a]); break;
                    default: break;
                }
            }

            // create the nodes and get a mass sum
            float sum_mass = 0.0f;
            if (level < NESTEDNESS) {
                xyz_t half = (x2y2 - x1y1) / 2;
                xyz_t canvas[4][2] = {{xyz_t(x1y1.x, x1y1.y, 0), xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0)},
                                    {xyz_t(x1y1.x, x1y1.y + half.y, 0), xyz_t(x1y1.x + half.x, x2y2.y, 0)},
                                    {xyz_t(x1y1.x + half.x, x1y1.y, 0), xyz_t(x2y2.x, x1y1.y + half.y, 0)},
                                    {xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0), xyz_t(x2y2.x, x2y2.y, 0)}};
                for (uint a = 0; a < 4; a++) {
                    if (region[a].size() > 0) {
                        node[a] = make_unique<Node>(level + 1); // create a new node
                        node[a]->setCanvasSize(canvas[a][0], canvas[a][1]);
                        sum_mass += node[a]->split(region[a]); // recursion split a node to the smaller nodes
                        // printsq(canvas[a][0], canvas[a][1]);
                    }
                }
            }
            mass_centre = Particle((x2y2 - x1y1) / 2 + x1y1, xyz_t(0, 0, 0), sum_mass);
            return sum_mass;
        }

        void printsq(xyz_t x1y1, xyz_t x2y2) { // todo: remove
            const uint VALUE_RANGE = 1000000;
            x1y1 = x1y1 / (VALUE_RANGE * 1.0f);
            x2y2 = x2y2 / (VALUE_RANGE * 1.0f);
            glColor3f(0.3f, 0.3f, 0.3f);
            glBegin(GL_LINE_STRIP);
            glVertex2f(x1y1.x, x1y1.y);
            glVertex2f(x1y1.x, x2y2.y);
            glVertex2f(x2y2.x, x2y2.y);
            glVertex2f(x2y2.x, x1y1.y);
            glVertex2f(x1y1.x, x1y1.y);
            glEnd();
        }

        Node(uint level)
        : level(level)
        {}
};