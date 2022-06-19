#include "Background.h"

Background::Background(std::vector<ID2D1Bitmap*> bitmaps, float x, float y): GameObject(bitmaps, x, y)
{
    currentBitmap = bitmaps[5];
}
void Background::update(int64_t timeElapsed, HWND hwnd){}
void Background::flipBitmap(){}

