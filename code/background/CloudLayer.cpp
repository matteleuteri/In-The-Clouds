#include "../headers/CloudLayer.h"

CloudLayer::CloudLayer(AnimationController *animationController, float x, float y, float xSpeed): GameObject(animationController, x, y, xSpeed)
{}

void CloudLayer::moveLayer()
{}

void CloudLayer::update(int32_t timeDiff)
{
    x += xSpeed;
}