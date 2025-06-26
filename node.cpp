#include "node.h"

#include "math.h"

long long int Node::maxFieldSize;

void Node::setParentFieldSize(xyz_t x1y1, xyz_t x2y2) {
    this->x1y1 = x1y1;
    this->x2y2 = x2y2;
    maxFieldSize = x2y2.x;
}

void Node::setFieldSize(xyz_t x1y1, xyz_t x2y2) {
    this->x1y1 = x1y1;
    this->x2y2 = x2y2;
}

double Node::dist(xyz_t from, xyz_t to) {
    xyz_t dist = to - from;
    double result = (dist.x*dist.x) + (dist.y*dist.y) + (dist.z*dist.z);
    return sqrt(result);
}

xyz_t Node::oldGravityInf(Particle* particle, Particle* target) {
    float G = 6.6742E-11;
    float r = dist(particle->getXYZ(), target->getXYZ());
    double gravity = (G * particle->getMass() * target->getMass()) / (r * r);

    xyz_t dist = target->getXYZ() - particle->getXYZ();
    float k = gravity / (abs(dist.x) + abs(dist.y));
    xyz_t gravity_vec = xyz_t(k * dist.x, k * dist.y, 0);
    return gravity_vec;
}

xyz_t Node::gravityInf(Particle* particle) {
    xyz_t gravity_vec(0, 0, 0);
    
    float s = dist(x1y1, x2y2);
    float r = dist(particle->getXYZ(), mass_centre.getXYZ());
    if (r == 0)             // if particle try to attract itself,
        return gravity_vec; // zero influence

    // part of bern-hat algorithm
    bool last_level = true;
    for (uint a = 0; a < daughter_count; a++)
        if (node.get()) {
            last_level = false; 
            break;
        }

    // influence calculation
    if (r / s > COEF || last_level) {
        float G = 6.6742E-13; // right vesion is 6.6742E-11
        // float G = 6.6742E-9;
        double gravity = (G * particle->getMass() * mass_centre.getMass()) / r; // todo: r --> (r * r)

        xyz_t vec = mass_centre.getXYZ() - particle->getXYZ();
        float k = gravity / r;
        gravity_vec = vec * k;

        // todo: reduild gravity power calculation
    }
    else {
        for (uint a = 0; a < daughter_count; a++) {
            if (node.get())
                gravity_vec += node[a].gravityInf(particle);
        }
    }

    return gravity_vec;
}

void Node::split(vector<Particle> particles) {
    switch (dimension) {
        case DIMENSION_2D: split2d(particles); break;
        case DIMENSION_3D: split3d(particles); break;
        default: break;
    }
}

float Node::split2d(vector<Particle> particles) {
    daughter_count = 4;
    if (particles.size() == 0) { // space without particles
        mass_centre = Particle(xyz_t(0, 0, 0), xyz_t(0, 0, 0), 0.0f);
        return 0.0f;
    }
    if (particles.size() == 1) { // space with only one particle
        mass_centre = particles[0];
        return particles[0].getMass();
    }

    // find where are particles
    node = make_unique<Node[]>(daughter_count);
    vector<Particle> regions[daughter_count];
    xyz_t node_size(x2y2 - x1y1); //todo: x1y1 --> x1y1z1
    for (uint a = 0; a < particles.size(); a++) {
        // inside what kind quad is particle
        int kind = daughter_count;
        kind = (particles[a].getX() > (node_size.x / 2 + x1y1.x)) ? (kind)     : (kind - 2);
        kind = (particles[a].getY() > (node_size.y / 2 + x1y1.y)) ? (kind - 1) : (kind - 2);
        // remember where particle stays
        regions[kind].push_back(particles[a]);
    }

    // create the nodes and get a mass sum
    float sum_mass = 0.0f;
    if (nestedness < MAX_NESTEDNESS) {
        xyz_t half = (x2y2 - x1y1) / 2; // todo: rename centre
        // todo: canvas[daughter_count, 2]
        xyz_t canvas[4][2] = {{xyz_t(x1y1.x, x1y1.y, 0), xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0)},
                              {xyz_t(x1y1.x, x1y1.y + half.y, 0), xyz_t(x1y1.x + half.x, x2y2.y, 0)},
                              {xyz_t(x1y1.x + half.x, x1y1.y, 0), xyz_t(x2y2.x, x1y1.y + half.y, 0)},
                              {xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0), xyz_t(x2y2.x, x2y2.y, 0)}};
        for (uint a = 0; a < daughter_count; a++) {
            node[a] = Node(dimension, nestedness + 1); // create a daughter node
            node[a].setFieldSize(canvas[a][0], canvas[a][1]);
            sum_mass += node[a].split2d(regions[a]); // recursion split the daughter node to the smaller nodes
            
            // <> (debug and just a nice visualization) <>
            printNodeSectors2d(canvas[a][0], canvas[a][1]);
        }
    }
    mass_centre = Particle((x2y2 - x1y1) / 2 + x1y1, xyz_t(0, 0, 0), sum_mass);
    return sum_mass;
}


float Node::split3d(vector<Particle> particles) {
    daughter_count = 8;
    if (particles.size() == 0) { // space without particles
        mass_centre = Particle(xyz_t(0, 0, 0), xyz_t(0, 0, 0), 0.0f);
        return 0.0f;
    }
    if (particles.size() == 1) { // space with only one particle
        mass_centre = particles[0];
        return particles[0].getMass();
    }

    // find where are particles
    node = make_unique<Node[]>(daughter_count);
    vector<Particle> regions[daughter_count];
    xyz_t node_size(x2y2 - x1y1); //todo: x1y1 --> x1y1z1
    for (uint a = 0; a < particles.size(); a++) {
        // inside what kind quad
        int kind = daughter_count;
        kind = (particles[a].getX() > (node_size.x / 2 + x1y1.x)) ? (kind)     : (kind - 4);
        kind = (particles[a].getY() > (node_size.y / 2 + x1y1.y)) ? (kind)     : (kind - 2);
        kind = (particles[a].getZ() > (node_size.z / 2 + x1y1.z)) ? (kind - 1) : (kind - 2);
        // remember where particle stays
        regions[kind].push_back(particles[a]);
    }

    // create the nodes and get a mass sum
    float sum_mass = 0.0f;
    if (nestedness < MAX_NESTEDNESS) {
        xyz_t half = (x2y2 - x1y1) / 2;
        xyz_t canvas[8][2] = {{xyz_t(x1y1.x, x1y1.y, x1y1.z),                   xyz_t(x1y1.x + half.x, x1y1.y + half.y, x1y1.z + half.z)},
                              {xyz_t(x1y1.x, x1y1.y + half.y, x1y1.z),          xyz_t(x1y1.x + half.x, x2y2.y, x1y1.z + half.z)},
                              {xyz_t(x1y1.x + half.x, x1y1.y, x1y1.z),          xyz_t(x2y2.x, x1y1.y + half.y, x1y1.z + half.z)},
                              {xyz_t(x1y1.x + half.x, x1y1.y + half.y, x1y1.z), xyz_t(x2y2.x, x2y2.y, x1y1.z + half.z)},

                              {xyz_t(x1y1.x, x1y1.y, x1y1.z + half.z),                   xyz_t(x1y1.x + half.x, x1y1.y + half.y, x2y2.z)},
                              {xyz_t(x1y1.x, x1y1.y + half.y, x1y1.z + half.z),          xyz_t(x1y1.x + half.x, x2y2.y, x2y2.z)},
                              {xyz_t(x1y1.x + half.x, x1y1.y, x1y1.z + half.z),          xyz_t(x2y2.x, x1y1.y + half.y, x2y2.z)},
                              {xyz_t(x1y1.x + half.x, x1y1.y + half.y, x1y1.z + half.z), xyz_t(x2y2.x, x2y2.y, x2y2.z)}
                            };
        for (uint a = 0; a < daughter_count; a++) {
            node[a] = Node(dimension, nestedness + 1); // create a daughter node
            node[a].setFieldSize(canvas[a][0], canvas[a][1]);
            sum_mass += node[a].split3d(regions[a]); // recursion split the daughter node to the smaller nodes
            
            // <> (debug and just a nice visualization) <>
            printNodeSectors3d(canvas[a][0], canvas[a][1]);
        }
    }

    mass_centre = Particle((x2y2 - x1y1) / 2 + x1y1, xyz_t(0, 0, 0), sum_mass);
    return sum_mass;
}

void Node::printNodeSectors2d(xyz_t x1y1, xyz_t x2y2) { // todo: remove
    x1y1 = x1y1 / maxFieldSize;
    x2y2 = x2y2 / maxFieldSize;
    const float brightness = 0.3f;
    glColor3f(brightness, brightness, brightness);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1y1.x, x1y1.y);
    glVertex2f(x1y1.x, x2y2.y);
    glVertex2f(x2y2.x, x2y2.y);
    glVertex2f(x2y2.x, x1y1.y);
    glVertex2f(x1y1.x, x1y1.y);
    glEnd();
}

void Node::printNodeSectors3d(xyz_t x1y1, xyz_t x2y2) { // todo: remove
    x1y1 = x1y1 / maxFieldSize;
    x2y2 = x2y2 / maxFieldSize;
    const float brightness = 0.3f;
    glColor3f(brightness, brightness, brightness);

    glBegin(GL_LINE_STRIP);
    // vertice 1
    glVertex3f(x1y1.x, x1y1.y, x1y1.z);
    glVertex3f(x1y1.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x1y1.y, x1y1.z);
    glVertex3f(x1y1.x, x1y1.y, x1y1.z);
    // vertice 2
    glVertex3f(x1y1.x, x1y1.y, x2y2.z);
    glVertex3f(x1y1.x, x2y2.y, x2y2.z);
    glVertex3f(x1y1.x, x2y2.y, x1y1.z);
    // vertice 3
    glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x2y2.y, x2y2.z);
    glVertex3f(x1y1.x, x2y2.y, x2y2.z);
    // vertice 3
    glVertex3f(x1y1.x, x1y1.y, x2y2.z);
    glVertex3f(x2y2.x, x1y1.y, x2y2.z);
    glVertex3f(x2y2.x, x2y2.y, x2y2.z);
    // vertice 3
    glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x1y1.y, x1y1.z);
    glVertex3f(x2y2.x, x1y1.y, x2y2.z);
    glEnd();

    return;
    // face 1 
    // glBegin(GL_LINE_LOOP);
    // glVertex3f(x1y1.x, x1y1.y, x1y1.z);
    // glVertex3f(x1y1.x, x2y2.y, x1y1.z);
    // glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    // glVertex3f(x2y2.x, x1y1.y, x1y1.z);
    // glEnd();
    // // face 2
    // glBegin(GL_LINE_LOOP);
    // glVertex3f(x1y1.x, x1y1.y, x2y2.z);
    // glVertex3f(x1y1.x, x2y2.y, x2y2.z);
    // glVertex3f(x2y2.x, x2y2.y, x2y2.z);
    // glVertex3f(x2y2.x, x1y1.y, x2y2.z);
    // glEnd();
    
    // glBegin(GL_LINES);
    // // indice 1
    // glVertex3f(x1y1.x, x1y1.y, x1y1.z);
    // glVertex3f(x1y1.x, x1y1.y, x2y2.z);
    // // indice 2
    // glVertex3f(x1y1.x, x2y2.y, x1y1.z);
    // glVertex3f(x1y1.x, x2y2.y, x2y2.z);
    // // indice 3
    // glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    // glVertex3f(x2y2.x, x2y2.y, x2y2.z);
    // // indice 4
    // glVertex3f(x2y2.x, x1y1.y, x1y1.z);
    // glVertex3f(x2y2.x, x1y1.y, x2y2.z);
    // glEnd();
}

void Node::printInfLine(xyz_t from, xyz_t to) {
    from = from / maxFieldSize;
    to = to / maxFieldSize;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(from.x, from.y, from.z);
    glVertex3f(to.x, to.y, to.z);
    glEnd();
}