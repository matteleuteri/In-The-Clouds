#include "headers/Scene.h"

Scene::Scene(int32_t currentTime, bool active, std::vector<AnimationController*> animationControllers, float x, float y) : isActive(active), x(x), y(y)
{    

    player = std::make_unique<Player>(animationControllers[0], 60.0f, 60.0f);

    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[1], 200.0f, 200.0f));
    worldChunks.push_back(std::make_unique<WorldChunk>(animationControllers[2], 600.0f, 600.0f));
    
    background = std::make_unique<Background>(animationControllers[3], 0.0f, 0.0f);    

    cloudLayers = std::make_unique<CloudLayer>(animationControllers[4], 0.0f, 0.0f);    
    
    lastTimestamp = GetTickCount();
}

void Scene::checkPlatformCollision(int32_t currentTime)
{
    // if(player->immune > 0) return;
    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        if(player->isActive && player->x > wc->x && player->x < wc->x + wc->width && std::abs(wc->y - (player->y + player->height)) <= 20)
        {
            player->landOn(wc.get());
            return;
        }
    }

    if(!player->isInAir)
    {
        WorldChunk *wc = player->chunkCurrentlyOn;
        if(!player->isInAir && (player->x > wc->width))
        {
            player->fallOff(1);
        }
        else if(!player->isInAir && (player->x < player->width))
        {
            player->fallOff(-1);
        }   
    }
}

void Scene::updateState(HWND hwnd, int32_t endTime, int32_t startTime)
{
    int32_t timeElapsed = endTime - startTime;
    
    // abstract this, this is trouble
    if(player->x > 1200)
    {
        x = 150;
    }

    player->update(timeElapsed, endTime);
    player->animate(endTime);

    cloudLayers->animate(endTime);

    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        wc->update(timeElapsed, endTime);
        // take endtime out of the above function, because naything that depends on endtime should be done elsewhere, right?
        wc->animate(endTime);
    }
    
    checkPlatformCollision(endTime);
}

void Scene::addForce(GameObject* gameObject, DIRECTION direction, float speed) 
{
    if(direction == RIGHT)
        gameObject->xSpeed = speed;
    else if(direction == LEFT)
        gameObject->xSpeed = -1 * speed;
}

void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], IDWriteTextFormat* pTextFormat_)
{
    renderTarget->BeginDraw();
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    drawBackground(renderTarget);
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    drawWorldChunks(renderTarget);
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    drawPlayer(renderTarget);
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(x, y));
    drawCloudLayer1(renderTarget);

    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    drawBM(renderTarget, background.get());
}

void Scene::drawCloudLayer1(ID2D1HwndRenderTarget* renderTarget)
{
    drawBM(renderTarget, cloudLayers.get());
}

void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget)
{
    for(std::unique_ptr<WorldChunk> &wc: worldChunks)
    {
        D2D1_SIZE_F size = wc->animation->bitmaps[wc->animation->currentFrame]->GetSize();
        drawBM(renderTarget, wc.get());    
    }
}

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
    if(!player->isInAir)
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(player->chunkCurrentlyOn->x - player->width, player->chunkCurrentlyOn->y - player->height));
    }
    drawBM(renderTarget, player.get());
}

void Scene::drawBM(ID2D1HwndRenderTarget* renderTarget, GameObject* g)
{
    renderTarget->DrawBitmap(g->animation->bitmaps[g->animation->currentFrame], 
                D2D1::RectF(g->x, g->y, g->x + g->width, g->y + g->height));
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