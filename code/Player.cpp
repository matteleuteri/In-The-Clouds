#include "headers/Player.h"

Player::Player(Animation *animation, float x, float y): GameObject(animation, x, y)
{
    isActive = true;
    goingRight = false;
    goingLeft = false;
    isInAir = true;
    width = animation->bitmaps[0]->GetSize().width;
    height = animation->bitmaps[0]->GetSize().height;
    inAirStartTime = animation->lastFlipTime;    
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

void Player::update(int64_t endTime,int64_t timeElapsed, HWND hwnd)
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

    x += (rightSpeed * speedScale * (timeElapsed / 25000));
    x -= (leftSpeed  * speedScale * (timeElapsed / 25000));

    if(isInAir)
    {
        doGravity(endTime);
    }

    if(x > 1440)    x = 0;
    else if(x < 0)  x = 1440;

    if(y > 720)     y = 0;
    else if(y < 0)  y = 720;

    if(immune > 0) immune -= 1;
}

void Player::pointPlayerTowards(POINT mousePosition)
{
    float xDistance = mousePosition.x - x;
    float yDistance = mousePosition.y - y;
    angle = ((float)atan(yDistance / xDistance) * (180.0f / PI)) + 90.0f; // offset needed to define origin rotation angle 

    if(mousePosition.x < x) angle += 180; // not sure why, but this is important
}

// can take game object as parameter eventually?
void Player::doGravity(int64_t currentTime)
{
    y += (currentTime - inAirStartTime)*(currentTime - inAirStartTime) / 100000000000000;
}

void Player::jump()
{
    OutputDebugStringA("jump!\n");
    isInAir = true;
    upSpeed += 3;
    // play the right animation
}