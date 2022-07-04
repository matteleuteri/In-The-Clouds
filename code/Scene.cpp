#include "headers/Scene.h"

Scene::Scene(int32_t currentTime, bool active, std::vector<AnimationController*> animationControllers, float x, float y, RECT *rc) : isActive(active), x(x), y(y), rc(rc)
{    
    player = std::make_unique<Player>(animationControllers[0], 600.0f, 60.0f);
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[1], 200.0f, 200.0f));
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[2], 600.0f, 600.0f));
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[3], 1000.0f, 500.0f));
    background = std::make_unique<Background>(animationControllers[4], 0.0f, 0.0f);    
    cloudLayers = std::make_unique<CloudLayer>(animationControllers[5], 0.0f, 0.0f);    
    lastTimestamp = GetTickCount();
}

static void drawBM(ID2D1HwndRenderTarget* renderTarget, GameObject* g)
{
    renderTarget->DrawBitmap(g->animation->bitmaps[g->animation->currentFrame], 
                D2D1::RectF(g->x, g->y, g->x + g->width, g->y + g->height));
}

void Scene::checkPlatformCollision(int32_t currentTime)
{
    if(player->immune > 0) return;

    if(!player->isInAir)
    {
        WorldChunk *wc = player->chunkCurrentlyOn;
        if(player->x > wc->width)
        {
            player->fallOff(1);
        }
        else if(player->x < player->width)
        {
            player->fallOff(-1);
        }   
    }

    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        if(player->isActive && player->x > wc->x && player->x < wc->x + wc->width && std::abs(wc->y - (player->y + player->height)) <= 20)
        {
            float newx = player->x - wc->x + player->width;
            player->landOn(wc.get(), newx, wc->y);
            return;
        }
    }
}

void Scene::updateState(HWND hwnd, int32_t endTime, int32_t startTime)
{
    int32_t timeElapsed = endTime - startTime;

    // the scene itself must also be updated
    x += (xSpeed * timeElapsed);

    player->update(timeElapsed);
    player->animate(endTime);

    cloudLayers->animate(endTime);

    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        wc->update(timeElapsed);
        wc->animate(endTime);
    }    
    checkPlatformCollision(endTime);
}

void Scene::movePlayer(GameObject* gameObject, float speed) 
{
    // try to get ????
    if(((rc->right - x) - (gameObject->x + gameObject->width) < 200 && speed > 0) || (gameObject->x - (rc->left - x) < 200 && speed < 0))
    {
       if(player->isInAir) // use xorigin instead
        xSpeed = -1 * speed;
    }
    else
    {
        xSpeed = 0.0f;
    }
    gameObject->xSpeed = speed;
}

void Scene::renderState(HWND hwnd, ID2D1HwndRenderTarget* renderTarget, IDWriteTextFormat* pTextFormat_)
{
    renderTarget->BeginDraw();
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    
    drawBackground(renderTarget);
    drawWorldChunks(renderTarget);
    drawPlayer(renderTarget);
    drawCloudLayer1(renderTarget);

    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, 0));
    drawBM(renderTarget, background.get());
}

void Scene::drawCloudLayer1(ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    drawBM(renderTarget, cloudLayers.get());
}

void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget)
{
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        D2D1_SIZE_F size = wc->animation->bitmaps[wc->animation->currentFrame]->GetSize();
        drawBM(renderTarget, wc.get());    
    }
}

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
    if(player->isInAir)
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    }
    else
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(player->chunkCurrentlyOn->x - player->width, player->chunkCurrentlyOn->y - player->height));
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