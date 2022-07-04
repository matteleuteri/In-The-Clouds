#include "headers/Player.h"

Player::Player(AnimationController *animationController, float x, float y): GameObject(animationController, x, y)
{
    isActive = true;
    isInAir = true;
    xOrigin = 0;
    yOrigin = 0;
    animation = animationController->animations[0];
    width = animation->bitmaps[0]->GetSize().width;
    height = animation->bitmaps[0]->GetSize().height;
    timeInAir = 0;
    immune = 0;
    ySpeed = 0;
}

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
    if(immune > 0)  immune -= 1;
    x += xSpeed * timeElapsed;
}

void Player::landOn(WorldChunk *wc, float newX, float newY)
{
    chunkCurrentlyOn = wc;
    isInAir = false;
    ySpeed = 0.0f;
    x = newX;
    y = 0;
}

void Player::setPosition(float x2, float y2)
{
    x = x2;
    y = y2;
}

void Player::fallOff(int i)
{
    immune = 100;
    isInAir = true;
    timeInAir = 0;
    if(i == 1) // are these conditions really needed?
    {
        setPosition(x +  chunkCurrentlyOn->x - width, y + chunkCurrentlyOn->y - height);
    }
    else if(i == -1)
    {
        setPosition(chunkCurrentlyOn->x, y + chunkCurrentlyOn->y - height);
    }
}

void Player::jump()
{
    // OutputDebugStringA("jumping\n");
    isInAir = true;
    timeInAir = 0;
    animation = animationController->animations[1];// only for a short time!!!
    immune = 20;
    x = x + chunkCurrentlyOn->x - width;
    y = y + chunkCurrentlyOn->y - height;
    ySpeed = -1.3f;
}
