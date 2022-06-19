#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include <d2d1.h>
#include <stdint.h>
#include <vector>

class GameObject
{
public:
    float x;
    float y;
    std::vector<ID2D1Bitmap*> bitmaps;
    ID2D1Bitmap *currentBitmap;
    // ID2D1Bitmap* bitmap;
    GameObject::GameObject(std::vector<ID2D1Bitmap*> bitmaps, float x, float y);
    virtual void GameObject::update(int64_t timeElapsed, HWND hwnd) = 0;
    virtual void GameObject::flipBitmap() = 0;
};

#endif