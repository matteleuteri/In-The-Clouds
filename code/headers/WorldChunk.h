#ifndef _WORLDCHUNK
#define _WORLDCHUNK

#include "GameObject.h"

class WorldChunk: public GameObject
{
public:
    int chunkID;
    int d;
    WorldChunk::WorldChunk(Animation* animation, float x, float y);
    void WorldChunk::update(int64_t timeElapsed, HWND hwnd);
    // void WorldChunk::flipBitmap();
};

#endif