#ifndef _CLOUDLAYER
#define _CLOUDLAYER

#include "GameObject.h"

class CloudLayer: public GameObject 
{
public:
    int xSpeedOffset;
    int ySpeedOffset;
    CloudLayer::CloudLayer(AnimationController *animationController, float x, float y, float xSpeed);
    void CloudLayer::update(int32_t timeDiff);
    void CloudLayer::moveLayer();
};

#endif