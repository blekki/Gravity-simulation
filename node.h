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
        unique_ptr<Node> node[4];
        
        // field size
        xyz_t x1y1;
        xyz_t x2y2;
        // field sum mass
        float mass;

        uint particle_count = 0;

        uint level; // nestedness level
        const uint NESTEDNESS = 8; // max level
        const int COEF = 4.0f; // coef of (size / dist)

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

        xyz_t gravityVec(xyz_t pos) { // todo: make parameter a pointer on particle
            // canvas
            float s = distCube(x2y2, x1y1); // right now sq
            xyz_t centre = (x2y2 - x1y1) / 2 + x1y1;
            float r = distCube(centre, pos); // right now sq

            // gravity
            float G = 6.6742E-11;
            float gravity = (G * pow(mass, 2)) / pow(r, 2);

            // xyz_t dist = centre - pos;
            // float k = dist.x / dist.y;
            // xyz_t vec(gravity * k, gravity / k, 0);
            // return vec;

            xyz_t vec(0, 0, 0);
            if (s / r > COEF) {
                xyz_t dist = centre - pos;
                float k = dist.x / dist.y;
                vec = xyz_t(gravity * k, gravity / k, 0);
                return vec;
            }
            return vec;
            // else {
            //     for (uint a = 0; a < 4; a++) {
            //         if (node[a])
            //             speed += node[a]->influence(pos);
            //     }
            // }

            // return speed;
        }

        uint split(vector<Particle> particles) {
            if (particles.size() == 0) // space without particles
                return 0;
            if (particles.size() == 1) // space with only one particle
                return 1;

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
                        this->mass += node[a]->split(region[a]); // recursion split a node to the smaller nodes
                        printsq(canvas[a][0], canvas[a][1]);
                    }
                }
            }
            return this->mass;
        }

        void printsq(xyz_t x1y1, xyz_t x2y2) { // todo: remove
            const uint VALUE_RANGE = 1000000;
            x1y1 = x1y1 / (VALUE_RANGE * 1.0f);
            x2y2 = x2y2 / (VALUE_RANGE * 1.0f);
            glColor3f(0.9f, 3.0f, 2.0f);
            glBegin(GL_LINE_STRIP);
            glVertex2f(x1y1.x, x1y1.y);
            glVertex2f(x1y1.x, x2y2.y);
            glVertex2f(x2y2.x, x2y2.y);
            glVertex2f(x2y2.x, x1y1.y);
            glVertex2f(x1y1.x, x1y1.y);
            glEnd();
        }

        Node(uint level)
        : mass(1E15), level(level) // mass(1E13)
        {}
};