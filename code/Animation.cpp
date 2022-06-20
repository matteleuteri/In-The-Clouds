#include "headers/Animation.h"

Animation::Animation(std::vector<ID2D1Bitmap*> bitmaps, int frames, int64_t lastFlipTime, int64_t timeFrame): 
            bitmaps(bitmaps), currentFrame(frames), lastFlipTime(lastFlipTime), timeFrame(timeFrame)
{}