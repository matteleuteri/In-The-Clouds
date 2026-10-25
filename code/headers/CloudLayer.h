#ifndef _CLOUDLAYER
#define _CLOUDLAYER

#include "GameObject.h"
#include <algorithm>

class CloudLayer: public GameObject 
{
public:
    int xSpeedOffset;
    int ySpeedOffset;
    CloudLayer(AnimationController *animationController, float x, float y, float xSpeed);
    void update(int32_t timeDiff);
    void moveLayer();
};

#endif