#include "headers/Scene.h"

Scene::Scene(int32_t currentTime, bool active, std::vector<AnimationController*> animationControllers, float x, float y, RECT *rc) : isActive(active), x(x), y(y), rc(rc)
{
    player = std::make_unique<Player>(animationControllers[0], 600.0f, 60.0f, 0.0f);
    camera = std::make_unique<Camera>(player.get(), 1280, 720);
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[1], 200.0f, 200.0f, 0.5f));
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[2], 600.0f, 600.0f, 0.5f));
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[3], 1000.0f, 500.0f, 0.5f));
    background = std::make_unique<Background>(animationControllers[4], 0.0f, 0.0f, 0.0f);
    cloudLayer1 = std::make_unique<CloudLayer>(animationControllers[5], 400.0f, 0.0f, 1.0f);
    cloudLayer2 = std::make_unique<CloudLayer>(animationControllers[6], 0.0f, 0.0f, 0.5f);
    lastTimestamp = GetTickCount();
}

static void drawBM(ID2D1HwndRenderTarget* renderTarget, GameObject* g)
{
    renderTarget->DrawBitmap(g->animation->bitmaps[g->animation->currentFrame], 
                D2D1::RectF(g->x, g->y, g->x + g->width, g->y + g->height));
}

void Scene::checkPlatformCollision(int32_t currentTime)
{
    if (player->immune > 0) {
        return;
    }

    if (!player->isInAir)
    {
        WorldChunk *wc = player->chunkCurrentlyOn;
        if (player->x < player->width/2 || player->x > wc->width - player->width/2)
        {
            player->fallOff();
            return;
        }   
    }

    for (std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        if (player->ySpeed > 0 && player->x > wc->x - player->width/3 && player->x < wc->x + wc->width + player->width/3 && std::abs(wc->y - (player->y + player->height)) <= 25)
        {
            float newx = player->x - wc->x + player->width/2;
            if(newx < player->width/2) newx = player->width/2;
            if(newx > wc->width - player->width/2) newx = wc->width - player->width/2;
            player->landOn(wc.get(), newx, wc->y);
            player->x = newx;
            player->chunkCurrentlyOn = wc.get();
            // Adjust for moving platform
            player->x += (wc->xSpeed * 0.0667f); // rough compensation
            return;
        }
    }
}

void Scene::updateState(HWND hwnd, int32_t endTime, int32_t startTime)
{
    int32_t timeElapsed = endTime - startTime;
    if(timeElapsed < 0) timeElapsed = 0;
    cloudLayer1->update(timeElapsed);
    cloudLayer1->animate(endTime);

    cloudLayer2->update(timeElapsed);
    cloudLayer2->animate(endTime);

    for (std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        wc->update(timeElapsed);
        wc->animate(endTime);
    }

    player->update(timeElapsed);
    player->animate(endTime);

    if(camera) camera->update(timeElapsed);

    checkPlatformCollision(endTime);
}

void Scene::renderState(HWND hwnd, ID2D1HwndRenderTarget* renderTarget, IDWriteTextFormat* pTextFormat_)
{
    renderTarget->BeginDraw();
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    
    drawBackground(renderTarget);
    drawCloudLayer(renderTarget, cloudLayer1.get());
    drawCloudLayer(renderTarget, cloudLayer2.get());
    drawWorldChunks(renderTarget);
    drawPlayer(renderTarget);

    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));
    drawBM(renderTarget, background.get());
}

void Scene::drawCloudLayer(ID2D1HwndRenderTarget* renderTarget, CloudLayer *cloundLayer)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));
    drawBM(renderTarget, cloundLayer);
}

void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));
    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        // D2D1_SIZE_F size = wc->animation->bitmaps[wc->animation->currentFrame]->GetSize();
        drawBM(renderTarget, wc.get());    
    }
}

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
    if(player->isInAir)
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));
    }
    else
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(player->chunkCurrentlyOn->x - player->width/2 + x, player->chunkCurrentlyOn->y - player->height + y));
    }
    drawBM(renderTarget, player.get());
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
