#ifndef _ANIMATION
#define _ANIMATION

#include <d2d1.h>
#include <vector>

class Animation
{
public:
    std::vector<ID2D1Bitmap*> bitmaps;
    int currentFrame;
    int64_t lastFlipTime;
    int64_t timeFrame;
    Animation::Animation(std::vector<ID2D1Bitmap*> bitmaps, int frames, int64_t lastFlipTime, int64_t timeFrame);
};

#endif