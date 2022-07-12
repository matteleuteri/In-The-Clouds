#ifndef _BACKGROUND
#define _BACKGROUND

#include "GameObject.h"

class Background : public GameObject
{
public:
    Background::Background(AnimationController *animationController, float x, float y, float xSpeed);
    void Background::update(int32_t timeElapsed);
};

#endif