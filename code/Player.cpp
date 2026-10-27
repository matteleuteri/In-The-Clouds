#include "headers/Player.h"

#include <cstdio>

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
        c1 = chunkCurrentlyOn->x + x - width / 2.0f;
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
        ySpeed += 0.002f * timeElapsed;
        y += timeElapsed * ySpeed;
    }
    if(y > 720)
    {
        y = 75;
        ySpeed = 0;
        timeInAir = 0;
        isInAir = true;
        chunkCurrentlyOn = nullptr; // avoid dangling pointer to cleaned-up chunk
    }
    if(immune > 0)
    {
        int delta = (int)(timeElapsed / 16.666f);
        if(delta < 1) delta = 1;
        immune -= (int32_t)delta;
    }
    if(immune < 0) immune = 0;
    x += xSpeed * timeElapsed;

    char dbg[256];
    float wcx = chunkCurrentlyOn ? chunkCurrentlyOn->x : -1.0f;
    float wcw = chunkCurrentlyOn ? chunkCurrentlyOn->width : -1.0f;
    snprintf(dbg, sizeof(dbg), "PLAYER: update: inAir=%d x=%.2f y=%.2f wx=%.2f wy=%.2f xs=%.2f ys=%.2f\n",
        isInAir ? 1 : 0, x, y, wcx, wcw, xSpeed, ySpeed);
    OutputDebugStringA(dbg);
}

void Player::landOn(WorldChunk *wc, float newX, float newY)
{
    chunkCurrentlyOn = wc;
    isInAir = false;
    ySpeed = 0.0f;
    timeInAir = 0;
    immune = 0; // clear immune so fall-off detection works immediately after landing
    if(animationController != NULL && animationController->animations.count(0) > 0)
    {
        animation = animationController->animations[0];
    }
    x = newX;
    y = 0.0f;
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
    std::array<float, 2> a = getAbsoluteCoordinates();
    isInAir = true;
    setPosition(a[0], a[1]);
    ySpeed = -1.3f;
}
