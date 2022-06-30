#include "headers/Player.h"

Player::Player(AnimationController *animationController, float x, float y): GameObject(animationController, x, y)
{
    isActive = true;
    isInAir = true;
    animation = animationController->animations[0];
    width = animation->bitmaps[0]->GetSize().width;
    height = animation->bitmaps[0]->GetSize().height;
    inAirStartTime = GetTickCount();
    immune = 0;
    ySpeed = 0;
}


void Player::update(int32_t timeElapsed, int32_t currentTime)
{
    x += xSpeed * timeElapsed;


    if(isInAir)
    {
        int dTime = currentTime - inAirStartTime;
        ySpeed = ySpeed  + ((dTime * 9.8f) / 100000);
        // ySpeed -= jumpSpeed;
        y += timeElapsed * ySpeed;
    }

    if(y > 720)
    {
        y = 75;
        ySpeed = 0;
        inAirStartTime = GetTickCount();
    }


    // x += (rightSpeed * speedScale * (timeElapsed / 2));
    // x -= (leftSpeed  * speedScale * (timeElapsed / 2));

    // // if(GetTickCount() - inAirStartTime <= 100)
    //     y -= upSpeed;

    // if(x > 1440)    x = 0;
    // else if(x < 0)  x = 1440;

    // if(y > 720)
    // {
    //     y = 20;
    //     inAirStartTime = GetTickCount();
    // }
    // else if(y < 0)  y = 720;

    // if(immune > 0) immune -= 1;
}

void Player::landOn(WorldChunk *wc)
{
    chunkCurrentlyOn = wc;
    isInAir = false;
    x = x - wc->x + width;
    y = 0.0f;
    ySpeed = 0.0f;
}

void Player::fallOff(int i)
{
    if(1 == 1)
    {
        immune = 100;
        x = x +  chunkCurrentlyOn->x - width;
        y = y + chunkCurrentlyOn->y - height;
        isInAir = true;
        inAirStartTime = GetTickCount();
    }
    else if(i == -1)
    {
        immune = 100;
        x = chunkCurrentlyOn->x;
        y = y + chunkCurrentlyOn->y - height;
        isInAir = true;
        inAirStartTime = GetTickCount();
    }
}

void Player::jump()
{
    OutputDebugStringA("jump!\n");
    isInAir = true;
    inAirStartTime = GetTickCount();
    animation = animationController->animations[1];// only for a short time
    immune = 100;
    x = x + chunkCurrentlyOn->x - width;
    y = y + chunkCurrentlyOn->y - height;
    isInAir = true;
    ySpeed = -1.3;
}
