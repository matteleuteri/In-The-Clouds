#ifndef _BACKGROUND
#define _BACKGROUND

#include "../headers/GameObject.h"

class Background : public GameObject
{
public:
    Background::Background(AnimationController *animationController, float x, float y);
    void Background::update(int32_t timeElapsed);
};

#endif