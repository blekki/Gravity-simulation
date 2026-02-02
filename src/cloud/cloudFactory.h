#pragma once

#include "enums.h"
#include "ICloud.h"
#include "cloud2d.h"
#include "cloud3d.h"

using namespace std;

class CloudFactory
{
    public:
        ICloud* createCloud(Dimension dimension);
        CloudFactory(){};
};