#ifndef _SCENE
#define _SCENE

#define PI 3.141592653589793238463f

#include <windows.h>
#include <stdint.h>
#include <d2d1.h>
#include <vector>
#include <memory>
#include <wincodec.h>
#include <combaseapi.h>
#include <Objbase.h>

#include "Player.h"
#include "../background/Background.h"

class Scene
{
public:
    bool isActive;
    std::unique_ptr<Player> player;
    std::unique_ptr<Background> background;
    void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget);
    Scene::Scene(int64_t currentTime, bool ia, std::vector<ID2D1Bitmap*> bitmaps);
    void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], IDWriteTextFormat* pTextFormat_);
    void Scene::updateState(HWND hwnd, int64_t startTime, int64_t endTime); 
};

#endif