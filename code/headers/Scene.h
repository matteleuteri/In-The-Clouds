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
#include "Background.h"
#include "CloudLayer.h"
#include "Camera.h"

class Scene
{
public:
    bool isActive;
    float x;
    float y;
    float width;
    float height;
    float xSpeed;
    RECT *rc;
    std::unique_ptr<Camera> camera;
    int32_t lastTimestamp;
    std::unique_ptr<Player> player;
    std::unique_ptr<Background> background;
    std::unique_ptr<CloudLayer> cloudLayer1;
    std::unique_ptr<CloudLayer> cloudLayer2;
    std::vector<std::unique_ptr<WorldChunk>> worldChunks;
    Scene::Scene(int32_t currentTime, bool active, std::vector<AnimationController*> animationControllers, float x, float y, RECT *rc);
    void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget);
    void Scene::renderState(HWND hwnd, ID2D1HwndRenderTarget* renderTarget, IDWriteTextFormat* pTextFormat_);
    void Scene::updateState(HWND hwnd, int32_t startTime, int32_t endTime); 
    void Scene::checkPlatformCollision(int32_t currentTime);
    void Scene::drawCloudLayer(ID2D1HwndRenderTarget* renderTarget, CloudLayer *cloundLayer);
};

#endif