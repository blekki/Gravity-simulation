#include "iostream"
#include "functional"

#include "cloud.h"
#include "massPoint.h"

void Cloud::newParticles(uint count) {
    for (uint i = 0; i < count; i++) {
        // position in the space
        float x = rand() % VALUE_RANGE * 2.0f - VALUE_RANGE;
        float y = rand() % VALUE_RANGE * 2.0f - VALUE_RANGE;
        xyz_t pos(x, y, 0);

        float sx = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;
        float sy = 0; //rand() % SPEED_RANGE * 2.0f - SPEED_RANGE;

        xyz_t speed(sx, sy, 0);
        particles.push_back(Particle(pos, speed));
    }
}

void Cloud::printsq(xyz_t pos1, xyz_t pos2) {
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

void Cloud::updatePos() {
    // a lamda function for finding a quadtree
    function<MassPoint(vector<Particle>, xyz_t, xyz_t)> quadtree;
    
    quadtree = [&](vector<Particle> quedBase, xyz_t pos1, xyz_t pos2) {
        if (quedBase.size() == 0) { // space without particles
            printsq(pos1, pos2);
            return MassPoint(xyz_t((pos2.x - pos1.x) / 2.0f, (pos2.y - pos1.y) / 2.0f, 0), 0); //todo: return mass too
        }
        if (quedBase.size() == 1) { // space with only one particle
            printsq(pos1, pos2);
            return MassPoint(xyz_t(quedBase[0].getX(), quedBase[0].getY(), 0), 1);
        }
        
        // find where are particles
        vector<Particle> node1, node2, node3, node4;
        xyz_t node_size(pos2 - pos1); //### 2 * VALUE_RANGE
        for (uint i = 0; i < quedBase.size(); i++) {
            // inside what kind quad
            int kind = 5;
            kind = (quedBase[i].getX() > node_size.x / 2) ? (kind) : (kind - 2);
            kind = (quedBase[i].getY() > node_size.y / 2) ? (kind - 1) : (kind - 2);
            // remember where stays particel
            switch (kind) {
                case 1: node1.push_back(quedBase[i]); cout << '1'; break;
                case 2: node2.push_back(quedBase[i]); cout << '2'; break;
                case 3: node3.push_back(quedBase[i]); cout << '3'; break;
                case 4: node4.push_back(quedBase[i]); cout << '4'; break;
                default: break;
            }
        }

        cout << "1" << endl;

        // find mass centre
        MassPoint centre[4];
        // node1
        xyz_t size10(pos1.x, pos1.y, 0);
        xyz_t size11(node_size.x / 2.0f, node_size.y / 2.0f, 0);
        centre[0] = quadtree(node1, size10, size11);
        // node2
        xyz_t size_20(pos1.x, node_size.y / 2.0f, 0);
        xyz_t size_21(node_size.x / 2.0f, pos2.y, 0);
        centre[1] = quadtree(node2, size_20, size_21);
        // node3
        xyz_t size_30(node_size.x / 2.0f, pos1.y, 0);
        xyz_t size_31(pos2.x, node_size.y / 2.0f, 0);
        centre[2] = quadtree(node3, size_30, size_31);
        // node4
        xyz_t size_40(node_size.x / 2.0f, node_size.y / 2.0f, 0);
        xyz_t size_41(pos2.x, pos2.y, 0);
        centre[3] = quadtree(node4, size_40, size_41);

        xyz_t resCentre(0, 0, 0);
        float massSum = 0.00001f;
        for (uint i = 0; i < 4; i++) { // every node
            massSum += centre->mass;
            resCentre.x += centre[i].pos.x;
            resCentre.y += centre[i].pos.y;
        }
        resCentre.x = resCentre.x / massSum;
        resCentre.y = resCentre.y / massSum;
        
        return MassPoint(resCentre, massSum);
    };
    xyz_t pos1(-VALUE_RANGE, -VALUE_RANGE, 0);
    xyz_t pos2(VALUE_RANGE, VALUE_RANGE, 0);
    MassPoint centre = quadtree(particles, pos1, pos2);


    for (uint i = 0; i < particles.size(); i++) {
        float x = (centre.pos.x - particles[i].getX()) / 100000.0f;
        float y = (centre.pos.y - particles[i].getY()) / 100000.0f;
        particles[i].addSpeed(xyz_t(x, y, 0));
        particles[i].updatePos();
    }
}

void Cloud::print() {

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (uint i = 0; i < particles.size(); i++) {

        float x = particles[i].getX() / (VALUE_RANGE * 1.0f);
        float y = particles[i].getY() / (VALUE_RANGE * 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}