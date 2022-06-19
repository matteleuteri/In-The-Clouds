#include "headers/Player.h"

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

void Player::update(int64_t timeElapsed, HWND hwnd)
{
    // doGravity();
    POINT mousePosition;
    BOOL cursorFound = GetCursorPos(&mousePosition);
    BOOL converted = ScreenToClient(hwnd, &mousePosition);
    if(cursorFound && converted) pointPlayerTowards(mousePosition);

    if(goingRight)
    {
        rightSpeed += 0.025f;
        if(rightSpeed > 1.0) // do these ones need f annotation for float?
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

    if(x > 1440)    x = 0;
    else if(x < 0)  x = 1440;

    if(y > 720)     y = 0;
    else if(y < 0)  y = 720;
}

void Player::pointPlayerTowards(POINT mousePosition)
{
    float xDistance = (mousePosition.x) - (x);
    float yDistance = (mousePosition.y) - (y);
    angle = ((float)atan(yDistance / xDistance) * (180.0f / PI)) + 90.0f; // offset needed to define origin rotation angle 

    if(mousePosition.x < x) angle += 180; // not sure why, but this is important
}

Player::Player(Animation *animation, float x, float y): GameObject(animation, x, y)
{
    isActive = true;
    goingRight = false;
    goingLeft = false;
    onPlatform = false;
    // width = 20;
    // height = 20;
    speedScale = 1.0f;
    leftSpeed = 0;
    rightSpeed = 0;
}

// void Player::flipBitmap()
// {
    
//     // do nothing until player has more bitmaps to animate with
// }

// can take game object as parameter eventually
void Player::doGravity()
{
    if(!onPlatform)
    y += 9.8f;//???
}

void Player::jump()
{
    OutputDebugStringA("jump!\n");
}