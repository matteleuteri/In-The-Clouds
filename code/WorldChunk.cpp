#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(std::vector<ID2D1Bitmap*> bitmaps, float x, float y): GameObject(bitmaps, x, y)
{
    // also could use speed, angle, whatever
    currentBitmap = bitmaps[3];// 3 and 4
    d = 1;
}

void WorldChunk::update(int64_t timeElapsed, HWND hwnd)
{
    x += (d * timeElapsed / 30000);
    if(x > 1000 || x < 100) d *= -1;
}

void WorldChunk::flipBitmap()
{}