#ifndef _WORLDCHUNK
#define _WORLDCHUNK

#include "GameObject.h"

class WorldChunk: public GameObject
{
public:
    int chunkID;
    float xMax;
    float xMin;
    WorldChunk(AnimationController *animationController, float x, float y, float xSpeed);
    void update(int32_t timeElapsed);
};

#endif