#include "Background.h"

Background::Background(ID2D1Bitmap* bitmap, float x, float y): GameObject(bitmap, x, y)
{}
void Background::update(int64_t timeElapsed, HWND hwnd){}
void Background::flipBitmap(){}

