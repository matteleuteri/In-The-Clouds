#include "headers/GameObject.h"

GameObject::GameObject(Animation *animation, float x, float y): animation(animation), x(x), y(y)
{
    D2D1_SIZE_F size = animation->bitmaps[0]->GetSize();
    width = size.width;
    height = size.height;
}

void GameObject::animate(int32_t currentTime) 
{
    if(currentTime - animation->lastFlipTime >= animation->timeFrame)
    {
        animation->currentFrame = (animation->currentFrame + 1) % animation->bitmaps.size();
        animation->lastFlipTime = currentTime;
        width = animation->bitmaps[animation->currentFrame]->GetSize().width;
        height = animation->bitmaps[animation->currentFrame]->GetSize().height;
    }
}