#include "headers/GameObject.h"

GameObject::GameObject(Animation *animation, float x, float y): animation(animation), x(x), y(y)
{}

void GameObject::animate(int64_t currentTime) 
{
    if(currentTime - animation->lastFlipTime >= animation->timeFrame)
    {
        animation->currentFrame = (animation->currentFrame + 1) % animation->bitmaps.size();
        animation->lastFlipTime = currentTime;
    }
}