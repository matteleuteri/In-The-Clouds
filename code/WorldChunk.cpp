#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(Animation* animation, float x, float y): GameObject(animation, x, y)
{
    // also could use speed, angle, whatever
    d = 1;
}

void WorldChunk::update(int32_t timeElapsed)
{
    x += (d * timeElapsed / 2);
    if(x > 1000 || x < 100) d *= -1;
}
