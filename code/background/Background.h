#ifndef _BACKGROUND
#define _BACKGROUND

#include "../headers/GameObject.h"

class Background : public GameObject
{
public:
    Background::Background(Animation* animation, float x, float y);
    void Background::update(int64_t timeElapsed, HWND hwnd);
    // void Background::flipBitmap();
};

#endif