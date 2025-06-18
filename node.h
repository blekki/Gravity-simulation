#pragma once

#include "stdlib.h"
#include <GL/gl.h>
#include "vector"
#include "memory"

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
        uint mass;

        uint level; // nestedness level
    
    public:
        void setCanvasSize(xyz_t x1y1, xyz_t x2y2) {
            this->x1y1 = x1y1;
            this->x2y2 = x2y2;
        }

        uint split(vector<Particle> particles) {
            // cout << "*";
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
            const uint NODE_COUNT = 4;
            xyz_t half = (x2y2 - x1y1) / 2;
            xyz_t canvas[4][2] = {{xyz_t(x1y1.x, x1y1.y, 0), xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0)},
                                  {xyz_t(x1y1.x, x1y1.y + half.y, 0), xyz_t(x1y1.x + half.x, x2y2.y, 0)},
                                  {xyz_t(x1y1.x + half.x, x1y1.y, 0), xyz_t(x2y2.x, x1y1.y + half.y, 0)},
                                  {xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0), xyz_t(x2y2.x, x2y2.y, 0)}};
            for (uint a = 0; a < NODE_COUNT; a++) {
                if (region[a].size() > 0) {
                    // cout << "s";
                    node[a] = make_unique<Node>(); // create a new node
                    node[a]->setCanvasSize(canvas[a][0], canvas[a][1]);
                    this->mass += node[a]->split(region[a]); // recursion split a node to the smaller nodes
                    // cout << " " << endl;
                }
            }
            printsq(x1y1, x2y2);
            return this->mass;
        }

        void printsq(xyz_t pos1, xyz_t pos2) {
            const uint VALUE_RANGE = 1000000;
            pos1 = pos1 / (VALUE_RANGE * 1.0f);
            pos2 = pos2 / (VALUE_RANGE * 1.0f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
            glVertex2f(pos1.x, pos1.y);
            glVertex2f(pos1.x, pos2.y);
            glVertex2f(pos2.x, pos2.y);
            glVertex2f(pos2.x, pos1.y);
            glVertex2f(pos1.x, pos1.y);
            glEnd();
        }

        Node(uint level) 
        : mass(0), level(level)
        {}
};