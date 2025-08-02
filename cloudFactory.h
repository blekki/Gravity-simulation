#pragma once

#include "enums.h"
#include "ICloud.h"
#include "cloud2d.h"
#include "cloud3d.h"

using namespace std;

class CloudFactory
{
    public:
        ICloud* createCloud(Dimension dimension) {
            ICloud* cloud = nullptr;
            switch (dimension) {
                case DIMENSION_2D: cloud = new Cloud2d; break;
                case DIMENSION_3D: cloud = new Cloud3d; break;
                default: break;
            }
            return cloud;
        }

        CloudFactory(){};
};