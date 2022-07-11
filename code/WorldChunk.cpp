#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(AnimationController *animationController, float x, float y): GameObject(animationController, x, y)
{
    // also could use speed, angle, whatever
    speed = 0.5f;
    xMax = x + 400;
    xMin = x - 300;
}

void WorldChunk::update(int32_t timeElapsed)
{
    x += (speed * timeElapsed / 5);
    if(x > xMax || x < xMin) 
    {
        speed *= -1;
    }
}
