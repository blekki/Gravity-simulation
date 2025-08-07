#include "node.h"

#include "math.h"
#include "functional"

#include "iostream"

// static variables
long long int Node::primalFieldSize;

// class methods
void Node::setField(Coord sizeFrom, Coord sizeTo) {
    this->sizeFrom = sizeFrom;
    this->sizeTo   = sizeTo;
    primalFieldSize = sizeTo.x; // ps: can be used each "sizeTo" axis
}

void Node::setDaughterField(Coord sizeFrom, Coord sizeTo) {
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
    Coord gravityVec = Coord(k * dist.x, k * dist.y, 0);
    return gravityVec;
}

Coord Node::gravityCalc(Particle* particle) {
    Coord gravityVec(0, 0, 0);
    
    // float s = distance(sizeFrom, sizeTo);
    float s = sizeTo.x - sizeFrom.x;
    float r = distance(particle->getPos(), mass_centre.getPos());
    // if particle tries to attract itself, return zero influence
    if (r == 0)
        return Coord(0, 0, 0);

    // gravity influence calculation
    bool last_layer = (daughters == nullptr) ? true : false;
    if (r / s > SIMULATION_QUALITY_COEF || last_layer) {
        // const float G = 6.6742E-13; // right vesion is 6.6742E-11
        // const float G = 6.6742E-11;
        // double gravity = (G * particle->getMass() * mass_centre.getMass()) / (r); // todo: r --> (r * r)
        // Coord vec = mass_centre.getPos() - particle->getPos();
        // vec.normalize();
        // float k = gravity / r;
        // gravityVec = vec * k;
        
        // todo: reduild gravity power calculation

        if (r <= 100 && !FIRST_LAYER)
            return Coord(0, 0, 0);

        const float G = 6.6742E-11;
        const uint SECOND_COUNT = 86400 * 100; // seconds per timeline (86400 = second per day)
        // calculations
        double gravity = (G * particle->getMass() * mass_centre.getMass()) / (r * r);
        Coord unit_vec = mass_centre.getPos() - particle->getPos();
        unit_vec.normalize();
        gravityVec = unit_vec * gravity * SECOND_COUNT;

    }
    else {
        if (daughters.get())
            for (uint a = 0; a < daughterCount; a++)
                gravityVec += daughters[a].gravityCalc(particle);
    }

    return gravityVec;
}

uint Node::whatKindRegion(Particle* particle) {
    // It's a binary searching algorithm
    // for finding place where stay the particle.
    // Algorithm works checks every axes and where is the particle in current space 
    // cuts everytime half available space.
    // (right or left from axes centre).
    // PS: 2d dimension has 4 regions, 3d dimension has 8 regions etc.

    int result = daughterCount; // default: the hightest value

    Coord node_size = sizeTo - sizeFrom;
    Coord pos       = particle->getPos(); // current particle position
    float center    = 0.0f;
    int max_index   = dimension - 1;

    // the higter index is used here
    center = (node_size.getAxis(max_index) / 2.0f) + sizeFrom.getAxis(max_index);
    result -= (pos.getAxis(max_index) < center) ? 2 : 1;

    // other indexes
    for (int index = max_index - 1; index >= 0; index--) {
        center = (node_size.getAxis(index) / 2.0f) + sizeFrom.getAxis(index);
        if (pos.getAxis(index) < center)
            result -= 2 * (max_index - index);
    }

    return result;
}

vector<pair<Coord, Coord>> Node::getDaughterSpaces() {
    vector<pair<Coord, Coord>> blocks; // vector full special (sizeFrom, sizeTo) pairs

    Coord center = (sizeTo + sizeFrom) / 2.0f; // actually a centre
    float quarter = (sizeTo.x - sizeFrom.x) / 4.0f;  // 1/4 of one axis
    Coord offset(quarter, 0, 0); // how the centre must be moved for be changed to x1y1 and x2y2 

    // Start of lambda func.
    // It dublicate the centre ((x2y2 - x1y1) / 2) as a pair of two position with some changed coords, but only by one dimension.
    // Repeat this action with the new position points pack until it fill all space.
    // Example:
    // for 2d dimension world do it 2 times (result = split space to 4 smaller spaces)
    // for 3d dimension world do it 3 times (result = split space to 8 smaller spaces)
    
    const int AVAILABLE_MAX_LAYER = dimension;
    // because fuction must be called the same times as dimension value. One time for each axis

    function<void(Coord, Coord, int)> mirror; // todo: rename
    mirror = [&](Coord pos, Coord offset, int layer) {
        // if have found final block centre
        if (layer == AVAILABLE_MAX_LAYER) {
            Coord from = addToEveryAxes(pos, -quarter);
            Coord to   = addToEveryAxes(pos,  quarter);
            blocks.push_back(pair(from, to)); // save results
            return;
        }

        // find two points at the same distance from the axis centre
        Coord left  = pos - offset;
        Coord right = pos + offset;
        
        // do it again with other axes
        offset.axesPermutation();
        layer++;
        mirror(left,  offset, layer); // for left  point
        mirror(right, offset, layer); // for right point
    };
    mirror(center, offset, FIRST_LAYER);

    return blocks;
}

void Node::splitter(vector<Particle> particles) {
    createDaughters(particles);
}

float Node::createDaughters(vector<Particle> particles) {
    if (particles.size() == 0) { // space without any particles
        mass_centre = Particle(Coord(0, 0, 0), Coord(0, 0, 0), 0.0f);
        return 0.0f; // zero mass
    }
    if (particles.size() == 1) { // space with only one particle
        mass_centre = particles[0];
        return particles[0].getMass();
    }

    // create the nodes and get a mass sum
    float sum_mass = 0.0f;
    if (nestedness < MAX_NESTEDNESS) {
        // find where are particles
        this->daughters = make_unique<Node[]>(daughterCount);
        vector<Particle> particlePacks[daughterCount];
        for (uint a = 0; a < particles.size(); a++) {
            // inside what kind quad is particle
            uint k = whatKindRegion(&particles[a]);
            particlePacks[k].push_back(particles[a]);
        }

        vector<pair<Coord, Coord>> spaces = getDaughterSpaces();
        for (uint a = 0; a < daughterCount; a++) {
            daughters[a] = Node(dimension, nestedness + 1); // create a daughter node
            daughters[a].setDaughterField(spaces[a].first, spaces[a].second);
            // come to next level
            sum_mass += daughters[a].createDaughters(particlePacks[a]); // recursion split the daughter node to the smaller nodes
        }
    }
    mass_centre = Particle((sizeTo - sizeFrom) / 2 + sizeFrom, Coord(0, 0, 0), sum_mass);
    return sum_mass;
}



void Node::printNodeSectors2d() { // print quad around node space
    Coord from = sizeFrom / primalFieldSize;
    Coord to   = sizeTo   / primalFieldSize;

    const float brightness = 0.3f;
    glColor3f(brightness, brightness, brightness);
    glBegin(GL_LINE_STRIP);
    glVertex2f(from.x, from.y);
    glVertex2f(from.x, to.y  );
    glVertex2f(to.x,   to.y  );
    glVertex2f(to.x,   from.y);
    glVertex2f(from.x, from.y);
    glEnd();

    // if node has daughters, check them too
    if (daughters != nullptr)
        for (uint i = 0; i < daughterCount; i++)
            daughters[i].printNodeSectors2d();
}

// todo: rename parameters
void Node::printNodeSectors3d() { // print cube around node space
    Coord from = sizeFrom / primalFieldSize;
    Coord to   = sizeTo   / primalFieldSize;

    const float brightness = 0.3f;
    glColor3f(brightness, brightness, brightness);
    glBegin(GL_LINE_STRIP);
    // iter 1
    glVertex3f(from.x, from.y, from.z);
    glVertex3f(from.x, to.y,   from.z);
    glVertex3f(to.x,   to.y,   from.z);
    glVertex3f(to.x,   from.y, from.z);
    glVertex3f(from.x, from.y, from.z);
    // iter 2
    glVertex3f(from.x, from.y, to.z  );
    glVertex3f(from.x, to.y,   to.z  );
    glVertex3f(from.x, to.y,   from.z);
    // iter 3
    glVertex3f(to.x,   to.y,   from.z);
    glVertex3f(to.x,   to.y,   to.z  );
    glVertex3f(from.x, to.y,   to.z  );
    // iter 4
    glVertex3f(from.x, from.y, to.z  );
    glVertex3f(to.x,   from.y, to.z  );
    glVertex3f(to.x,   to.y,   to.z  );
    // iter 5
    glVertex3f(to.x,   to.y,   from.z);
    glVertex3f(to.x,   from.y, from.z);
    glVertex3f(to.x,   from.y, to.z  );
    glEnd();
    
    // if node has daughters, check them too
    if (daughters != nullptr)
        for (uint i = 0; i < daughterCount; i++)
            daughters[i].printNodeSectors3d();
}

void Node::printAllSectors() {
    switch (dimension) {
        case DIMENSION_2D: printNodeSectors2d(); break;
        case DIMENSION_3D: printNodeSectors3d(); break;
        default: break;
    }
}

void Node::printInfluenceLines(Coord from, Coord to) {
    from = from / primalFieldSize;
    to   = to   / primalFieldSize;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(from.x, from.y, from.z);
    glVertex3f(to.x, to.y, to.z);
    glEnd();
}

// ### CONSTRUCTORS ###

// private:
Node::Node(Dimension dimension, uint nestedness) {
    this->dimension = dimension;
    this->nestedness = nestedness;
    this->daughterCount = pow(2, (uint) dimension);
    this->daughters = nullptr;
}

// public:
Node::Node(Dimension dimension) {
    this->dimension = dimension;
    this->nestedness = 0;
    this->daughterCount = pow(2, (uint) dimension);
    this->daughters = nullptr;
}

Node::Node(){
    this->dimension = DIMENSION_2D;
    this->nestedness = 0;
    this->daughterCount = pow(2, (uint) dimension);
    this->daughters = nullptr;
}