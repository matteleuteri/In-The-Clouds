#include "headers/Player.h"

Player::Player(Animation *animation, float x, float y): GameObject(animation, x, y)
{
    isActive = true;
    goingRight = false;
    goingLeft = false;
    isInAir = true;
    width = animation->bitmaps[0]->GetSize().width;
    height = animation->bitmaps[0]->GetSize().height;
    inAirStartTime = GetTickCount();
    speedScale = 1.0f;
    immune = 0;
    rightSpeed = 0;
    leftSpeed = 0;
    upSpeed = 0;
    downSpeed = 0;
}

void Player::moveTowardsZero(DIRECTION direction) 
{
    float* dirSpeed = 0;

    if(direction == LEFT)  dirSpeed = &leftSpeed;
    else if(direction == RIGHT) dirSpeed = &rightSpeed;

    if(*dirSpeed == 0) return;
    
    if(*dirSpeed > 0) 
    {
        *dirSpeed -= 0.01f;
        if(*dirSpeed < 0) *dirSpeed = 0;
    }
}

void Player::update(int32_t timeElapsed)
{

    if(goingRight)
    {
        rightSpeed += 0.025f;
        if(rightSpeed > 1.0)
        {
            rightSpeed = 1.0;
        }
    }
    else moveTowardsZero(RIGHT);

    if(goingLeft)
    {
        (leftSpeed) += 0.025f;
        if(leftSpeed > 1.0)
        {
            leftSpeed = 1.0;
        }
    }
    else moveTowardsZero(LEFT);

    x += (rightSpeed * speedScale * (timeElapsed / 2));
    x -= (leftSpeed  * speedScale * (timeElapsed / 2));

    // if(isInAir)
    // {
    //     doGravity(endTime);
    // }

    if(x > 1440)    x = 0;
    else if(x < 0)  x = 1440;

    if(y > 720)     y = 0;
    else if(y < 0)  y = 720;

    if(immune > 0) immune -= 1;
}

void Player::doGravity(int32_t endTime, int32_t physicsStartTime)
{
    // this happens once every 0.02 seconds
    int32_t timeElapsed = (endTime - physicsStartTime);

    y += timeElapsed;
    // y += (timeElapsed * timeElapsed * 9.8 );
    // y += (GetTickCount() / 1000 - inAirStartTime) * (GetTickCount() / 1000 - inAirStartTime) * 9.8f;
}

void Player::jump()
{
    OutputDebugStringA("jump!\n");
    isInAir = true;
    upSpeed += 3;
}