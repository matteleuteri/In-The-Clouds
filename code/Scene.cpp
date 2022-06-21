#include "headers/Scene.h"

Scene::Scene(int64_t currentTime, bool active, std::vector<std::vector<ID2D1Bitmap*>> bitmaps) : isActive(active)
{    
    Animation* playerAnm = new Animation(bitmaps[0], 0, currentTime, 1000000);
    Animation* chunk1Anm = new Animation(bitmaps[1], 0, currentTime, 1000000);
    Animation* chunk2Anm = new Animation(bitmaps[2], 0, currentTime, 1000000);
    Animation* bAnm = new Animation(bitmaps[3], 0, currentTime, 1000000);

    player = std::make_unique<Player>(playerAnm, 600.0f, 600.0f);
    background = std::make_unique<Background>(bAnm, 0.0f, 0.0f);
    // make this a function to load all chunks at once
    chunk1 = std::make_unique<WorldChunk>(chunk1Anm, 200.0f, 200.0f);
    chunk2 = std::make_unique<WorldChunk>(chunk2Anm, 600.0f, 600.0f);
}

void Scene::checkPlatformCollision()
{
    if(!player->onPlatform && player->x > chunk1->x && player->x < chunk1->x + chunk1->width && std::abs(chunk1->y - (player->y + player->height)) <= 3)
    {
        OutputDebugStringA("collide!\n");
        player->onPlatform = true;
        player->x = player->x - chunk1->x + player->width;
        player->leftSpeed = 0.0f;// maybe dont go straight to 0, but def slow down
        player->rightSpeed = 0.0f;
        player->y = 0.0f;
    }

    if(player->onPlatform && (player->x > chunk1->width ))
    {
        // reset origin and current coordinates
        player->x = player->x + chunk1->x - player->width;
        player->y = player->y + chunk1->y - player->height + 3;
        player->onPlatform = false;
    }
    else if(player->onPlatform && (player->x < 4))
    {
        // reset origin and current coordinates
        player->x = chunk1->x - player->width;
        player->y = player->y + chunk1->y - player->height + 3;
        player->onPlatform = false;
    }
    // else if jump
}

void Scene::updateState(HWND hwnd, int64_t endTime, int64_t startTime)
{
    int64_t timeElapsed = endTime - startTime;
    
    checkPlatformCollision();

    player->update(timeElapsed, hwnd);
    player->animate(endTime);

    chunk1->update(timeElapsed, hwnd);
    chunk1->animate(endTime);
    
    chunk2->update(timeElapsed, hwnd);
    chunk2->animate(endTime);
}

void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3], IDWriteTextFormat* pTextFormat_)
{
    renderTarget->BeginDraw();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));
    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0,{0,0}));
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    // draw border of window
    // D2D1_RECT_F border = D2D1::RectF((float)rc->left, (float)rc->top, (float)rc->right, (float)rc->bottom);
    // renderTarget->DrawRectangle(border, brushes[0]);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    drawBackground(renderTarget);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    drawWorldChunks(renderTarget);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    drawPlayer(renderTarget);
    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    drawBM(renderTarget, background.get());
}

void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_SIZE_F size = chunk1->animation->bitmaps[chunk1->animation->currentFrame]->GetSize();
    drawBM(renderTarget, chunk1.get());
    drawBM(renderTarget, chunk2.get());    
}

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
    // D2D1_POINT_2F center = {};
    // center.x = player->x;
    // center.y = player->y;
    // D2D1_SIZE_F size = player->animation->bitmaps[player->animation->currentFrame]->GetSize();

    if(player->onPlatform)
    {
        renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(chunk1->x - player->width, chunk1->y - player->height));
    }

    drawBM(renderTarget, player.get());
    // renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));
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
