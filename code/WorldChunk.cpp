#include "headers/WorldChunk.h"

WorldChunk::WorldChunk(ID2D1Bitmap* bitmap, float x, float y): GameObject(bitmap, x, y)
{
    // also could use speed, angle, whatever
}

void WorldChunk::update(int64_t timeElapsed, HWND hwnd)
{}

void WorldChunk::flipBitmap()
{}