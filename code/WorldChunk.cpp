#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(AnimationController *animationController, float x, float y): GameObject(animationController, x, y)
{
    // also could use speed, angle, whatever
    d = 1;
    xMax = x + 400;
    xMin = x - 300;
}

void WorldChunk::update(int32_t timeElapsed)
{
    x += (d * timeElapsed / 5);
    if(x > xMax || x < xMin) 
    {
        d *= -1;
    }
}
