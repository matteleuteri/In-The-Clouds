#ifndef _WORLDCHUNK
#define _WORLDCHUNK

#include "GameObject.h"

class WorldChunk: public GameObject
{
public:
    int chunkID;
    int d;
    WorldChunk::WorldChunk(std::vector<ID2D1Bitmap*> bitmaps, float x, float y);
    void WorldChunk::update(int64_t timeElapsed, HWND hwnd);
    void WorldChunk::flipBitmap();
};
#endif