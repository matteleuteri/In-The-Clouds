#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include <d2d1.h>
#include <stdint.h>
#include <vector>

#include "Animation.h"

class GameObject
{
public:
    float x;
    float y;
    float width;
    float height;
    Animation *animation;
    GameObject::GameObject(Animation *animation, float x, float y);
    virtual void GameObject::update(int32_t timeElapsed) = 0;
    virtual void GameObject::animate(int32_t currentTime);
};

#endif