#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(Animation* animation, float x, float y): GameObject(animation, x, y)
{
    // also could use speed, angle, whatever
    d = 1;
}

void WorldChunk::update(int64_t endTime, int64_t timeElapsed, HWND hwnd)
{
    x += (d * timeElapsed / 30000);
    if(x > 1000 || x < 100) d *= -1;
}
