#include "headers/Scene.h"

Scene::Scene(int64_t currentTime, bool active, std::vector<std::vector<ID2D1Bitmap*>> bitmaps) : isActive(active)
{    
    Animation* playerAnm = new Animation(bitmaps[0], 0);
    Animation* chunkAnm = new Animation(bitmaps[1], 0);
    Animation* bAnm = new Animation(bitmaps[2], 0);

    player = std::make_unique<Player>(playerAnm, 600.0f, 600.0f);
    background = std::make_unique<Background>(bAnm, 0.0f, 0.0f);
    // make this a function to load all chunks at once
    chunk1 = std::make_unique<WorldChunk>(chunkAnm, 200.0f, 20.0f);
    chunk2 = std::make_unique<WorldChunk>(chunkAnm, 400.0f, 400.0f);
}

void Scene::updateState(HWND hwnd, int64_t endTime, int64_t startTime)
{
    int64_t timeElapsed = endTime - startTime;
    player->update(timeElapsed, hwnd);
    chunk1->update(timeElapsed, hwnd);
    chunk2->update(timeElapsed, hwnd);
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
    drawBackground(renderTarget);
    drawWorldChunks(renderTarget);
    drawPlayer(renderTarget);
    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_SIZE_F size = background->animation->bitmaps[background->animation->currentFrame]->GetSize();
    renderTarget->DrawBitmap(background->animation->bitmaps[background->animation->currentFrame], D2D1::RectF(
                background->x, 
                background->y, 
                background->x + size.width, 
                background->y + size.height)); 
}

void Scene::drawWorldChunks(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_SIZE_F size = chunk1->animation->bitmaps[chunk1->animation->currentFrame]->GetSize();
    renderTarget->DrawBitmap(chunk1->animation->bitmaps[chunk1->animation->currentFrame], D2D1::RectF(
                chunk1->x,
                chunk1->y,
                chunk1->x + size.width,
                chunk1->y + size.height)); 


    D2D1_SIZE_F size2 = chunk2->animation->bitmaps[chunk2->animation->currentFrame]->GetSize();
    renderTarget->DrawBitmap(chunk2->animation->bitmaps[chunk2->animation->currentFrame], D2D1::RectF(
                chunk2->x,
                chunk2->y,
                chunk2->x + size2.width,
                chunk2->y + size2.height));     
}

void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget)
{
    D2D1_POINT_2F center = {};
    center.x = player->x;
    center.y = player->y;
    D2D1_SIZE_F size = player->animation->bitmaps[player->animation->currentFrame]->GetSize();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(player->angle, center));
    renderTarget->DrawBitmap(player->animation->bitmaps[player->animation->currentFrame], D2D1::RectF(
                player->x - (size.width / 2), 
                player->y - (size.height / 2), 
                player->x + (size.width / 2), 
                player->y + (size.height / 2)));
    renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(0, center));
}

// void Scene::drawBM(GameObject* g)
// {
//     size = g->bitmap->GetSize();
//     renderTmrget->DrawBitmap(g->>bitmap, D2D1::RectF(
//                 g->x - (size.width / 2), 
//                 g->y - (size.height / 2), 
//                 g->x + (size.width / 2), 
//                 g->y + (size.height / 2)));
// }

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
