#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include <d2d1.h>
#include <stdint.h>
#include <vector>

#include "Animation.h"

class GameObject
{
public:
    float x;
    float y;
    // std::vector<ID2D1Bitmap*> bitmaps;
    // ID2D1Bitmap *currentBitmap;
    Animation *animation;
    // ID2D1Bitmap* bitmap;
    GameObject::GameObject(Animation *animation, float x, float y);
    virtual void GameObject::update(int64_t timeElapsed, HWND hwnd) = 0;
    virtual void GameObject::flipBitmap();
};

#endif