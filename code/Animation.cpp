#include "headers/Animation.h"

Animation::Animation(std::vector<ID2D1Bitmap*> bitmaps, int frames): bitmaps(bitmaps), currentFrame(frames)
{}