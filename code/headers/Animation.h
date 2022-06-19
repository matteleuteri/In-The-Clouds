#ifndef _ANIMATION
#define _ANIMATION

#include <d2d1.h>
#include <vector>

class Animation
{
public:
    std::vector<ID2D1Bitmap*> bitmaps;
    int currentFrame;
    Animation::Animation(std::vector<ID2D1Bitmap*> bitmaps, int frames);
};

#endif