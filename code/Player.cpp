#include "headers/Player.h"

Player::Player(AnimationController *animationController, float x, float y, float xSpeed): GameObject(animationController, x, y, xSpeed)
{
    isActive = true;
    isInAir = true;
    animation = animationController->animations[0];
    width = animation->bitmaps[0]->GetSize().width;
    height = animation->bitmaps[0]->GetSize().height;
    timeInAir = 0;
    immune = 0;
    ySpeed = 0;
}

std::array<float, 2> Player::getAbsoluteCoordinates()
{
    float c1;
    float c2;

    if(isInAir)
    {
        c1 = x;
        c2 = y;
    }
    else
    {
        // we need to get the players coordinates wrt the screen, 
        // using the coordinates wrt a world chunk 
        c1 = chunkCurrentlyOn->x + x - width;
        c2 = chunkCurrentlyOn->y - height;
    }

    std::array<float, 2> a = { c1, c2 };
    return a;
}


#include "headers/Player.h"
#include <cmath>

void Player::update(int32_t timeElapsed)
{
    if(isInAir)
    {
        timeInAir += timeElapsed;
        ySpeed += ((timeInAir* 9.8f) / 100000);
        y += timeElapsed * ySpeed;
    }
    if(y > 720)
    {
        y = 75;
        ySpeed = 0;
        timeInAir = 0;
    }
    if(immune > 0)
    {
        int delta = (int)(timeElapsed / 16.666f);
        if(delta < 1) delta = 1;
        immune -= (int32_t)delta;
    }
    if(immune < 0) immune = 0;
    x += xSpeed * timeElapsed;
}

void Player::landOn(WorldChunk *wc, float newX, float newY)
{
    chunkCurrentlyOn = wc;
    isInAir = false;
    ySpeed = 0.0f;
    timeInAir = 0;
    if(animationController != NULL && animationController->animations.count(0) > 0)
    {
        animation = animationController->animations[0];
    }
    setPosition(newX, 0.0f);
}

void Player::setPosition(float x2, float y2)
{
    x = x2;
    y = y2;
}

void Player::fallOff()
{
    immune = 20;
    timeInAir = 0;
    if(animationController != NULL && animationController->animations.count(0) > 0)
    {
        animation = animationController->animations[0];
    }
    std::array<float, 2> a = getAbsoluteCoordinates();
    setPosition(a[0], a[1]);
    isInAir = true;
}

void Player::jump()
{
    timeInAir = 0;
    if(animationController != NULL && animationController->animations.count(1) > 0)
    {
        animation = animationController->animations[1];
    }
    immune = 20;
    std::array<float, 2> a = getAbsoluteCoordinates();
    isInAir = true;
    setPosition(a[0], a[1]);
    ySpeed = -1.3f;
}
