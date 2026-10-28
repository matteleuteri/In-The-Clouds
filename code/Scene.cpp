#include "headers/Scene.h"

#include <cstdio>
#include <cmath>

Scene::Scene(int32_t currentTime, bool active, std::vector<AnimationController*> animationControllers, float x, float y, RECT *rc) : isActive(active), x(x), y(y), rc(rc), nextChunkSpawnX(0.0f), nextCloudSpawnX(0.0f), chunkControllerIndex(1), cloudControllerIndex(5)
{
    this->animationControllers = animationControllers;
    player = std::make_unique<Player>(animationControllers[0], 600.0f, 60.0f, 0.0f);
    camera = std::make_unique<Camera>(player.get(), 1280, 720);
    background = std::make_unique<Background>(animationControllers[4], 0.0f, 0.0f, 0.0f);
    srand((unsigned int)GetTickCount());
    // Seed initial chunks/clouds so the player has something to land on
    spawnChunk(600.0f, 600.0f, animationControllers[1]);
    nextChunkSpawnX = 1000.0f;
    spawnCloud(400.0f, 0.0f, animationControllers[5]);
    spawnCloud(900.0f, 50.0f, animationControllers[6]);
    nextCloudSpawnX = 1400.0f;
    lastTimestamp = GetTickCount();
}

static void drawBM(ID2D1HwndRenderTarget* renderTarget, GameObject* g)
{
    renderTarget->DrawBitmap(g->animation->bitmaps[g->animation->currentFrame], 
                D2D1::RectF(g->x, g->y, g->x + g->width, g->y + g->height));
}

void Scene::checkPlatformCollision(int32_t currentTime)
{
    // Walk off edge with coyote time: when the player reaches the edge, start
    // a grace period (coyoteTime) during which they can walk back onto the
    // platform. During this time they begin falling but cannot re-land on the
    // same chunk, preventing the "wall at the edge" and "snap back" issues.
    if (!player->isInAir && player->immune <= 0 && player->chunkCurrentlyOn)
    {
        WorldChunk *wc = player->chunkCurrentlyOn;
        if (player->x < player->width/2 || player->x > wc->width - player->width/2)
        {
            if (player->coyoteTime <= 0)
            {
                // Convert to absolute screen coords before going airborne,
                // just like fallOff() and jump() do.
                std::array<float, 2> a = player->getAbsoluteCoordinates();
                player->setPosition(a[0], a[1]);
                player->coyoteTime = 8;
                player->isInAir = true;
                player->ySpeed = 0.0f;
                player->immune = 20;
            }
        }
        else
        {
            player->coyoteTime = 0; // back on platform, reset grace period
        }
    }

    // Landing check — always active, but skip the chunk we just fell off
    // during coyote time so we don't snap back onto it immediately.
    for (std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        if (player->coyoteTime > 0 && wc.get() == player->chunkCurrentlyOn)
            continue;
        if (player->ySpeed > 0 && player->x > wc->x - player->width/3 && player->x < wc->x + wc->width + player->width/3 && std::abs(wc->y - (player->y + player->height)) <= 25)
        {
            float newx = player->x - wc->x + player->width/2;
            if(newx < player->width/2) newx = player->width/2;
            if(newx > wc->width - player->width/2) newx = wc->width - player->width/2;
            player->landOn(wc.get(), newx, wc->y);
            char dbg[256];
            snprintf(dbg, sizeof(dbg), "PLAYER: LAND wcx=%.2f wcw=%.2f newx=%.2f px=%.2f py=%.2f valid=[%.2f, %.2f]\n",
                wc->x, wc->width, newx, player->x, player->y, player->width/2, wc->width - player->width/2);
            OutputDebugStringA(dbg);
            return;
        }
    }
}

void Scene::updateState(HWND hwnd, int32_t endTime, int32_t startTime)
{
    int32_t timeElapsed = endTime - startTime;
    if(timeElapsed < 0) timeElapsed = 0;
    for (auto &cl : cloudLayers)
    {
        cl->update(timeElapsed);
        cl->animate(endTime);
    }    for (std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        wc->update(timeElapsed);
        wc->animate(endTime);
    }

    player->update(timeElapsed);
    player->animate(endTime);

    // Deadzone camera: keep the player horizontally in the middle third of
    // the screen. When the player leaves that band, shift the world so they
    // are placed back at the nearest third boundary.
    float playerWorldCenterX = player->x + player->width / 2.0f;
    if (!player->isInAir && player->chunkCurrentlyOn)
    {
        // grounded: player->x is chunk-relative; world center = chunk->x + player->x
        playerWorldCenterX = player->chunkCurrentlyOn->x + player->x;
    }
    if (camera) camera->update(timeElapsed, playerWorldCenterX);

    // Procedural generation: spawn chunks/clouds just before they become
    // visible, and remove ones that have fallen behind the camera.
    if (camera)
    {
        float camRight = camera->x + (float)camera->width;
        const float SPAWN_AHEAD = 500.0f;
        const float CHUNK_SPACING = 500.0f;
        while (nextChunkSpawnX < camRight + SPAWN_AHEAD)
        {
            float cy = 200.0f + (float)(rand() % 400);
            spawnChunk(nextChunkSpawnX, cy, animationControllers[1 + (chunkControllerIndex % 3)]);
            nextChunkSpawnX += CHUNK_SPACING + (float)(rand() % 200);
            chunkControllerIndex++;
        }
        cleanupChunks(camera->x);

        float camRightCloud = camera->x + (float)camera->width;
        const float CLOUD_SPAWN_AHEAD = 600.0f;
        const float CLOUD_SPACING = 400.0f;
        while (nextCloudSpawnX < camRightCloud + CLOUD_SPAWN_AHEAD)
        {
            float cy = (float)(rand() % 300);
            spawnCloud(nextCloudSpawnX, cy, animationControllers[5 + (cloudControllerIndex % 2)]);
            nextCloudSpawnX += CLOUD_SPACING + (float)(rand() % 300);
            cloudControllerIndex++;
        }
        cleanupClouds(camera->x);
    }

    checkPlatformCollision(endTime);
}

void Scene::renderState(HWND hwnd, ID2D1HwndRenderTarget* renderTarget, IDWriteTextFormat* pTextFormat_)
{
    renderTarget->BeginDraw();
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    
    drawBackground(renderTarget);
    for (auto &cl : cloudLayers)
    {
        drawCloudLayer(renderTarget, cl.get());
    }
    drawWorldChunks(renderTarget);
    drawPlayer(renderTarget);

    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    if (!background || background->animation->bitmaps.empty()) return;
    D2D1_SIZE_F size = background->animation->bitmaps[background->animation->currentFrame]->GetSize();
    float bgWidth = size.width;
    float bgHeight = size.height;
    if (bgWidth <= 0.0f) return;
    float screenW = (float)camera->width;
    float camX = camera->x;

    // screen position where the background tile at world x=0 appears: -camX
    // Wrap into [0, bgWidth) then tile across the screen so there is no black
    // gap at either end as the camera pans past the image's natural width.
    float offset = -camX;
    float wrapped = fmodf(offset, bgWidth);
    if (wrapped < 0.0f) wrapped += bgWidth;

    ID2D1Bitmap* bmp = background->animation->bitmaps[background->animation->currentFrame];
    const float overlap = 1.0f; // overlap tiles by 1px to hide sub-pixel seams
    for (float sx = wrapped - bgWidth - overlap; sx < screenW + overlap; sx += bgWidth)
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(sx, 0.0f));
        renderTarget->DrawBitmap(bmp, D2D1::RectF(0.0f, 0.0f, bgWidth + overlap, bgHeight));
    }
}

void Scene::drawCloudLayer(ID2D1HwndRenderTarget* renderTarget, CloudLayer *cloundLayer)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(-camera->x, 0.0f));
    drawBM(renderTarget, cloundLayer);
}
void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(-camera->x, 0.0f));
    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        drawBM(renderTarget, wc.get());    
    }
}

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
    if (player->isInAir)
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(-camera->x, 0.0f));
    }
    else
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(
            player->chunkCurrentlyOn->x - player->width / 2.0f - camera->x,
            player->chunkCurrentlyOn->y - player->height));
    }
    drawBM(renderTarget, player.get());
}

void Scene::spawnChunk(float x, float y, AnimationController* ac)
{
    worldChunks.push_back(std::make_unique<WorldChunk>(ac, x, y, 0.5f));
}

void Scene::spawnCloud(float x, float y, AnimationController* ac)
{
    cloudLayers.push_back(std::make_unique<CloudLayer>(ac, x, y, 1.0f));
}

void Scene::cleanupChunks(float cameraX)
{
    const float DESPAWN_BEHIND = -600.0f;
    for (auto it = worldChunks.begin(); it != worldChunks.end(); )
    {
        WorldChunk *wc = it->get();
        if (wc->x + wc->width < cameraX + DESPAWN_BEHIND)
        {
            // Avoid dangling pointer if this is the chunk the player stands on
            if (player->chunkCurrentlyOn == wc)
            {
                player->chunkCurrentlyOn = nullptr;
                player->isInAir = true;
            }
            it = worldChunks.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Scene::cleanupClouds(float cameraX)
{
    const float DESPAWN_BEHIND = -800.0f;
    for (auto it = cloudLayers.begin(); it != cloudLayers.end(); )
    {
        CloudLayer *cl = it->get();
        if (cl->x + cl->width < cameraX + DESPAWN_BEHIND)
        {
            it = cloudLayers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// D2D1_RECT_F layoutRect = D2D1::RectF(
// static_cast<FLOAT>(rc->left),
// static_cast<FLOAT>(rc->top),
// static_cast<FLOAT>(rc->right - rc->left),
// static_cast<FLOAT>(rc->bottom - rc->top));
// const wchar_t* wszText_ = L"This is my text, it has a null terminating charcetr\n";
// UINT32 cTextLength_ = 53;// check for overflow
// renderTarget->DrawText(
// wszText_,        // The string to render.
// cTextLength_,    // The string's length.
// pTextFormat_,    // The text format.
// layoutRect,       // The region of the window where the text will be rendered.
// brushes[0]);
