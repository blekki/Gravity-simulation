#include "node.h"

int Node::maxFieldSize;

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
    double result = (dist.x*dist.x) + (dist.y*dist.y);// + (dist.z*dist.z);
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

xyz_t Node::gravityInf(Particle* particle) { // todo: make parameter a pointer on particle
    xyz_t gravity_vec(0, 0, 0);
    
    float s = dist(x1y1, x2y2);
    float r = dist(particle->getXYZ(), mass_centre.getXYZ());
    if (r == 0)             // if particle try to attract itself,
        return gravity_vec; // zero influence

    // part of bern-hat algorithm
    bool last_level = true;
    for (uint a = 0; a < 4; a++)
        if (node[a])
            last_level = false;

    // influence calculation
    if (r / s > COEF || last_level) {
        float G = 6.6742E-14; // right vesion is 6.6742E-11
        double gravity = (G * particle->getMass() * mass_centre.getMass()) / r; // todo: r --> (r * r)

        xyz_t dist = mass_centre.getXYZ() - particle->getXYZ();
        float a = gravity / (abs(dist.x) + abs(dist.y)); // todo: some restruct
        gravity_vec = xyz_t(a * dist.x, a * dist.y, 0);
    }
    else {
        for (uint a = 0; a < 4; a++) {
            if (node[a])
                gravity_vec += node[a]->gravityInf(particle);
        }
    }

    return gravity_vec;
}

float Node::split(vector<Particle> particles) {
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
        
        // remember where particle stays
        switch (kind) { // todo: make simpler
            case 1: region[0].push_back(particles[a]); break;
            case 2: region[1].push_back(particles[a]); break;
            case 3: region[2].push_back(particles[a]); break;
            case 4: region[3].push_back(particles[a]); break;
            default: break;
        }
    }

    // create the nodes and get a mass sum
    float sum_mass = 0.0f;
    if (nestedness < MAX_NESTEDNESS) {
        xyz_t half = (x2y2 - x1y1) / 2;
        xyz_t canvas[4][2] = {{xyz_t(x1y1.x, x1y1.y, 0), xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0)},
                              {xyz_t(x1y1.x, x1y1.y + half.y, 0), xyz_t(x1y1.x + half.x, x2y2.y, 0)},
                              {xyz_t(x1y1.x + half.x, x1y1.y, 0), xyz_t(x2y2.x, x1y1.y + half.y, 0)},
                              {xyz_t(x1y1.x + half.x, x1y1.y + half.y, 0), xyz_t(x2y2.x, x2y2.y, 0)}};
        for (uint a = 0; a < 4; a++) {
            if (region[a].size() > 0) {
                node[a] = make_unique<Node>(nestedness + 1); // create a daughter node
                node[a]->setFieldSize(canvas[a][0], canvas[a][1]);
                sum_mass += node[a]->split(region[a]); // recursion split the daughter node to the smaller nodes
                // <> print nodes (debug and just a nice visualization) <>
                // printNodeSectors(canvas[a][0], canvas[a][1]);
            }
        }
    }
    mass_centre = Particle((x2y2 - x1y1) / 2 + x1y1, xyz_t(0, 0, 0), sum_mass);
    return sum_mass;
}

void Node::printNodeSectors(xyz_t x1y1, xyz_t x2y2) { // todo: remove
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

void Node::printInfLine(xyz_t from, xyz_t to) {
    from = from / maxFieldSize;
    to = to / maxFieldSize;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(from.x, from.y);
    glVertex2f(to.x, to.y);
    glEnd();
}