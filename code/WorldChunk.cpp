#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(AnimationController *animationController, float x, float y, float xSpeed): GameObject(animationController, x, y, xSpeed)
{
    xMax = x + 400;
    xMin = x - 300;
}

void WorldChunk::update(int32_t timeElapsed)
{
    x += (xSpeed * timeElapsed / 5); // whats going on here
    if(x > xMax || x < xMin) 
    {
        xSpeed *= -1;
    }
}
