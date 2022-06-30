#ifndef _CLOUDLAYER
#define _CLOUDLAYER

#include "GameObject.h"

class CloudLayer: public GameObject 
{
public:
    // std::vector<>
    int xSpeedOffset;
    int ySpeedOffset;
    CloudLayer::CloudLayer(AnimationController *animationController, float x, float y);
    void CloudLayer::update(int32_t timeDiff, int32_t currentTime);
    void CloudLayer::moveLayer();
};

#endif