#ifndef _WORLDCHUNK
#define _WORLDCHUNK

#include "GameObject.h"

class WorldChunk: public GameObject
{
public:
    int chunkID;
    int d;
    WorldChunk::WorldChunk(AnimationController *animationController, float x, float y);
    void WorldChunk::update(int32_t timeElapsed);
    // void WorldChunk::flipBitmap();
};

#endif