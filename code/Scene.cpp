#include "headers/Scene.h"

Scene::Scene(int32_t currentTime, bool active, std::vector<std::vector<ID2D1Bitmap*>> bitmaps) : isActive(active)
{    
    Animation* playerIdleAnm = new Animation(bitmaps[0], 0, currentTime, 100);
    Animation* playerJumpAnm = new Animation(bitmaps[1], 0, currentTime, 100);
    std::map<int, Animation*> playerAnimations;
    playerAnimations[0] = playerIdleAnm;
    playerAnimations[1] = playerJumpAnm;
    AnimationController *playerAnimationController = new AnimationController(playerAnimations);
    player = std::make_unique<Player>(playerAnimationController, 60.0f, 60.0f);

    Animation* chunk1Anm = new Animation(bitmaps[2], 0, currentTime, 100);
    std::map<int, Animation*> chunk1Animations;
    chunk1Animations[0] = chunk1Anm;
    AnimationController *chunk1AnimationController = new AnimationController(chunk1Animations);
    worldChunks.push_back(std::make_unique<WorldChunk>(chunk1AnimationController, 200.0f, 200.0f));

    Animation* chunk2Anm = new Animation(bitmaps[3], 0, currentTime, 100);
    std::map<int, Animation*> chunk2Animations;
    chunk2Animations[0] = chunk2Anm;
    AnimationController *chunk2AnimationController = new AnimationController(chunk2Animations);
    worldChunks.push_back(std::make_unique<WorldChunk>(chunk2AnimationController, 600.0f, 600.0f));
    
    Animation* bAnm = new Animation(bitmaps[4], 0, currentTime, 100);
    std::map<int, Animation*> backgroundAnimations;
    backgroundAnimations[0] = bAnm;
    AnimationController *backgroundAnimationController = new AnimationController(backgroundAnimations);
    background = std::make_unique<Background>(backgroundAnimationController, 0.0f, 0.0f);    

    // Animation* cloudLayer1Anm = new Animation(bitmaps[5], 0, currentTime, 100);
    // std::map<int, Animation*> cloudLayer1Animations;
    // cloudLayer1Animations[0] = bAnm;
    // AnimationController *cloudLayer1AnimationController = new AnimationController(cloudLayer1Animations);
    // cloudLayer1 = std::make_unique<CloudLayer>(cloudLayer1AnimationController, 0.0f, 0.0f);    
    // lastTimestamp = GetTickCount();
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
    
    player->update(timeElapsed, endTime);
    player->animate(endTime);

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
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    drawBackground(renderTarget);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    drawWorldChunks(renderTarget);
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    drawPlayer(renderTarget);
    
    // renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    // drawCloudLayer1(renderTarget);

    renderTarget->EndDraw();  
}

void Scene::drawBackground(ID2D1HwndRenderTarget* renderTarget)
{
    drawBM(renderTarget, background.get());
}

void Scene::drawCloudLayer1(ID2D1HwndRenderTarget* renderTarget)
{
    drawBM(renderTarget, cloudLayer1.get());
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