#include "headers/WorldChunk.h"

#define X_DIFF_CONST 400

WorldChunk::WorldChunk(AnimationController *animationController, float x, float y, float xSpeed): GameObject(animationController, x, y, xSpeed)
{
    xMax = x + X_DIFF_CONST;
    xMin = x - X_DIFF_CONST;
}

void WorldChunk::update(int32_t timeElapsed)
{
    x += (xSpeed * timeElapsed / 15);
    if(x > xMax || x < xMin) 
    {
        xSpeed *= -1;
    }
}