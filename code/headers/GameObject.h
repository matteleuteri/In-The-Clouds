#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include <d2d1.h>
#include <stdint.h>
#include <array>

class GameObject
{
public:
    float x;
    float y;
    std::array<ID2D1Bitmap*, 1> bitmaps;
    ID2D1Bitmap* bitmap;
    GameObject::GameObject(ID2D1Bitmap* bitmap, float x, float y);
    virtual void GameObject::update(int64_t timeElapsed, HWND hwnd) = 0;
    virtual void GameObject::flipBitmap() = 0;
};

#endif