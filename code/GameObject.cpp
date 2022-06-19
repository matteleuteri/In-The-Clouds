#include "headers/GameObject.h"

GameObject::GameObject(Animation *animation, float x, float y): animation(animation), x(x), y(y)
{}

void GameObject::flipBitmap()
{
    animation->currentFrame = (animation->currentFrame + 1) % animation->bitmaps.size();
}
