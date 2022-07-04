#ifndef _WORLDCHUNK
#define _WORLDCHUNK

#include "GameObject.h"

class WorldChunk: public GameObject
{
public:
    int chunkID;
    int d;
    float xMax;
    float xMin;
    WorldChunk::WorldChunk(AnimationController *animationController, float x, float y);
    void WorldChunk::update(int32_t timeElapsed);
};

#endif