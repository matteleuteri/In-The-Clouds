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
#include <map>
#include "Player.h"
#include "WorldChunk.h"
#include "AnimationController.h"
#include "../background/Background.h"

class Scene
{
public:
    bool isActive;
    int32_t lastTimestamp;
    std::unique_ptr<Player> player;
    std::unique_ptr<Background> background;
    std::vector<std::unique_ptr<WorldChunk>> worldChunks;
    
    Scene::Scene(int32_t currentTime, bool active, std::vector<std::vector<ID2D1Bitmap*>> bitmaps);
    void Scene::drawBM(ID2D1HwndRenderTarget* renderTarget, GameObject* g);
    void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget);
    void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], IDWriteTextFormat* pTextFormat_);
    void Scene::updateState(HWND hwnd, int32_t startTime, int32_t endTime); 
    void Scene::checkPlatformCollision(int32_t currentTime);
    void Scene::addForce(GameObject* gameObject, DIRECTION direction, float speed);
};

#endif