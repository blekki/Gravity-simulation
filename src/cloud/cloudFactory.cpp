#include "cloudFactory.h"

ICloud* CloudFactory::createCloud(Dimension dimension) {
    ICloud* cloud = nullptr;
    switch (dimension) {
        case DIMENSION_2D: cloud = new Cloud2d; break;
        case DIMENSION_3D: cloud = new Cloud3d; break;
        default: break;
    }
    return cloud;
}