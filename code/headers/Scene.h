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
#include <cstdlib>
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
    std::vector<std::unique_ptr<CloudLayer>> cloudLayers;
    std::vector<std::unique_ptr<WorldChunk>> worldChunks;
    std::vector<AnimationController*> animationControllers;
    float nextChunkSpawnX;
    float nextChunkSpawnXLeft;
    float nextCloudSpawnX;
    float nextCloudSpawnXLeft;
    int chunkControllerIndex;
    int cloudControllerIndex;
    Scene(int32_t currentTime, bool active, std::vector<AnimationController*> animationControllers, float x, float y, RECT *rc);
    void drawWorldChunks(ID2D1HwndRenderTarget* renderTarget);
    void drawBackground(ID2D1HwndRenderTarget* renderTarget);
    void drawPlayer(ID2D1HwndRenderTarget* renderTarget);
    void renderState(HWND hwnd, ID2D1HwndRenderTarget* renderTarget, IDWriteTextFormat* pTextFormat_);
    void updateState(HWND hwnd, int32_t endTime, int32_t startTime); 
    void checkPlatformCollision(int32_t currentTime);
    void drawCloudLayer(ID2D1HwndRenderTarget* renderTarget, CloudLayer *cloundLayer);
    void spawnChunk(float x, float y, AnimationController* ac, float xSpeed);
    void spawnCloud(float x, float y, AnimationController* ac, float xSpeed);
    void cleanupChunks(float cameraX);
    void cleanupClouds(float cameraX);
};

#endif