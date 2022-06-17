#ifndef _BACKGROUND
#define _BACKGROUND

#include "../headers/GameObject.h"

class Background : public GameObject
{
public:
    Background::Background(ID2D1Bitmap* bitmap, float x, float y);
    void Background::update(int64_t timeElapsed, HWND hwnd);
    void Background::flipBitmap();
};

#endif