#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(AnimationController *animationController, float x, float y): GameObject(animationController, x, y)
{
    // also could use speed, angle, whatever
    d = 1;
}

void WorldChunk::update(int32_t timeElapsed)
{
    x += (d * timeElapsed / 2);
    if(x > 1000 || x < 100) d *= -1;
}
