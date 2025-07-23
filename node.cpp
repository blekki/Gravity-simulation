#include "node.h"

#include "math.h"
#include "functional"

#include "iostream"

long long int Node::fistParrentFieldSize;

void Node::setFieldSize(Coord sizeFrom, Coord sizeTo) {
    this->sizeFrom = sizeFrom;
    this->sizeTo   = sizeTo;
    fistParrentFieldSize = sizeTo.x; // ps: can be used each "sizeTo" axis
}

void Node::setDaughterFieldSize(Coord sizeFrom, Coord sizeTo) {
    this->sizeFrom = sizeFrom;
    this->sizeTo   = sizeTo;
}

double Node::distance(Coord from, Coord to) {
    double dist = (to - from).diagonaleSq();
    return sqrt(dist);
}

Coord Node::addToEveryAxes(Coord vec, float value) {
    Coord result;
    result.x = vec.x + value;
    result.y = vec.y + value;
    result.z = vec.z + value;
    return result;
}

Coord Node::oldGravityCalc(Particle* particle, Particle* target) {
    float G = 6.6742E-11;
    float r = distance(particle->getPos(), target->getPos());
    double gravity = (G * particle->getMass() * target->getMass()) / (r * r);

    Coord dist = target->getPos() - particle->getPos();
    float k = gravity / (abs(dist.x) + abs(dist.y));
    Coord gravity_vec = Coord(k * dist.x, k * dist.y, 0);
    return gravity_vec;
}

Coord Node::gravityCalc(Particle* particle) {
    Coord gravity_vec(0, 0, 0);
    
    float s = distance(sizeFrom, sizeTo);
    float r = distance(particle->getPos(), mass_centre.getPos());
    if (r == 0)             // if particle try to attract itself,
        return Coord(0, 0, 0); // zero influence

    // part of barnes-hut algorithm
    bool last_level = true;
    for (uint a = 0; a < daughterNodeCount; a++)
        if (daughterNodes.get()) {
            last_level = false; 
            break;
        }

    // influence calculation
    if (r / s > SIMULATION_QUALITY_COEF || last_level) {
        float G = 6.6742E-13; // right vesion is 6.6742E-11
        // float G = 6.6742E-9;
        double gravity = (G * particle->getMass() * mass_centre.getMass()) / (r); // todo: r --> (r * r)

        Coord vec = mass_centre.getPos() - particle->getPos();
        float k = gravity / r;
        gravity_vec = vec * k;

        // todo: reduild gravity power calculation
    }
    else {
        for (uint a = 0; a < daughterNodeCount; a++) {
            if (daughterNodes.get())
                gravity_vec += daughterNodes[a].gravityCalc(particle);
        }
    }

    return gravity_vec;
}

vector<pair<Coord, Coord>> Node::division() {
    vector<pair<Coord, Coord>> blocks; // array full (coordFrom, coordTo) coords per line

    Coord center = (sizeTo + sizeFrom) / 2.0f;      // actually a centre
    float quarter = (sizeTo.x - sizeFrom.x) / 4.0f; // 1/4 of one coord length
    Coord offset(quarter, 0, 0);              // how the centre must be moved for be changed to x1y1 and x2y2 

    // Start of lambda func.
    // It dublicate the centre ((x2y2 - x1y1) / 2) as a pair of two position with some changed coords, but only by one dimension.
    // Repeat this action with the new position points pack until it fill all space.
    // Example:
    // for 2d dimension world do it 2 times (result = split space to 4 smaller spaces)
    // for 3d dimension world do it 3 times (result = split space to 8 smaller spaces)
    
    const int MAX_LAYER = dimension;
    // because fuction must be called the same times as dimension value. One time for each axis

    function<void(Coord, Coord, int)> mirror; // todo: rename
    mirror = [&](Coord pos, Coord offset, int layer) {
        if (layer == MAX_LAYER) {
            Coord coord1 = addToEveryAxes(pos, -quarter);
            Coord coord2 = addToEveryAxes(pos,  quarter);
            blocks.push_back(pair(coord1, coord2)); // save results
            return;
        }

        Coord minus = pos - offset;
        Coord plus  = pos + offset;

        offset.axesPermutation();
        layer++;
        mirror(minus, offset, layer);
        mirror(plus,  offset, layer);
    };
    mirror(center, offset, FIRST_LAYER);

    return blocks;
}

uint Node::whatKindRegion(Particle* particle) {
    Coord coord = particle->getPos();
    Coord node_size(sizeTo - sizeFrom);

    int kind = daughterNodeCount;
    int max_index = dimension - 1;
    for (int index = max_index - 1; index >= 0; index--) {
        float center = node_size.getAxis(index) / 2 + sizeFrom.getAxis(index);
        if (coord.getAxis(index) < center)
            kind -= 2 * (max_index - index);
    }

    float center = node_size.getAxis(max_index) / 2.0f + sizeFrom.getAxis(max_index);
    kind = (coord.getAxis(max_index) < center) ? (kind - 2) : (kind - 1);

    return kind;
}

void Node::split(vector<Particle> particles) {
    // switch (dimension) {
    //     case DIMENSION_2D: split2d(particles); break;
    //     case DIMENSION_3D: split3d(particles); break;
    //     default: break;
    // }
    splitSpace(particles);
}

float Node::splitSpace(vector<Particle> particles) {
    if (particles.size() == 0) { // space without particles
        mass_centre = Particle(Coord(0, 0, 0), Coord(0, 0, 0), 0.0f);
        return 0.0f;
    }
    if (particles.size() == 1) { // space with only one particle
        mass_centre = particles[0];
        return particles[0].getMass();
    }

    // find where are particles
    daughterNodes = make_unique<Node[]>(daughterNodeCount);
    vector<Particle> regions[daughterNodeCount];
    Coord node_size(sizeTo - sizeFrom);
    for (uint a = 0; a < particles.size(); a++) {
        // inside what kind quad is particle
        uint kind = whatKindRegion(&particles[a]);
        regions[kind].push_back(particles[a]);
    }

    // create the nodes and get a mass sum
    float sum_mass = 0.0f;
    if (nestedness < MAX_NESTEDNESS) {
        vector<pair<Coord, Coord>> canvas = division();
        for (uint a = 0; a < daughterNodeCount; a++) {
            daughterNodes[a] = Node(dimension, nestedness + 1); // create a daughter node
            daughterNodes[a].setDaughterFieldSize(canvas[a].first, canvas[a].second);
            sum_mass += daughterNodes[a].splitSpace(regions[a]); // recursion split the daughter node to the smaller nodes
            
            // <> (debug and just a nice visualization) <>
            bool debugMode = false; //todo: remove and make another method
            if (debugMode) {
                switch (dimension) {
                    case DIMENSION_2D: printNodeSectors2d(canvas[a].first, canvas[a].second); break;
                    case DIMENSION_3D: printNodeSectors3d(canvas[a].first, canvas[a].second); break;
                    default: break;
                }
            }
        }
    }
    mass_centre = Particle((sizeTo - sizeFrom) / 2 + sizeFrom, Coord(0, 0, 0), sum_mass);
    return sum_mass;
}


void Node::printNodeSectors2d(Coord x1y1, Coord x2y2) { // print quad around every dot
    x1y1 = x1y1 / fistParrentFieldSize;
    x2y2 = x2y2 / fistParrentFieldSize;
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

// todo: rename parameters
void Node::printNodeSectors3d(Coord x1y1, Coord x2y2) { // print cube around every dot
    x1y1 = x1y1 / fistParrentFieldSize;
    x2y2 = x2y2 / fistParrentFieldSize;
    const float brightness = 0.3f;
    glColor3f(brightness, brightness, brightness);
    glBegin(GL_LINE_STRIP);
    // iter 1
    glVertex3f(x1y1.x, x1y1.y, x1y1.z);
    glVertex3f(x1y1.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x1y1.y, x1y1.z);
    glVertex3f(x1y1.x, x1y1.y, x1y1.z);
    // iter 2
    glVertex3f(x1y1.x, x1y1.y, x2y2.z);
    glVertex3f(x1y1.x, x2y2.y, x2y2.z);
    glVertex3f(x1y1.x, x2y2.y, x1y1.z);
    // iter 3
    glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x2y2.y, x2y2.z);
    glVertex3f(x1y1.x, x2y2.y, x2y2.z);
    // iter 3
    glVertex3f(x1y1.x, x1y1.y, x2y2.z);
    glVertex3f(x2y2.x, x1y1.y, x2y2.z);
    glVertex3f(x2y2.x, x2y2.y, x2y2.z);
    // iter 3
    glVertex3f(x2y2.x, x2y2.y, x1y1.z);
    glVertex3f(x2y2.x, x1y1.y, x1y1.z);
    glVertex3f(x2y2.x, x1y1.y, x2y2.z);
    glEnd();
}

void Node::printInfLine(Coord from, Coord to) { // inf = influence
    from = from / fistParrentFieldSize;
    to   = to   / fistParrentFieldSize;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(from.x, from.y, from.z);
    glVertex3f(to.x, to.y, to.z);
    glEnd();
}