#ifndef _WORLDCHUNK
#define _WORLDCHUNK

#include "GameObject.h"

class WorldChunk: public GameObject
{
public:
    int chunkID;
    WorldChunk::WorldChunk(ID2D1Bitmap* bitmap, float x, float y);
    void WorldChunk::update(int64_t timeElapsed, HWND hwnd);
    void WorldChunk::flipBitmap();
};
#endif