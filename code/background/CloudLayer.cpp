#include "../headers/CloudLayer.h"

CloudLayer::CloudLayer(AnimationController *animationController, float x, float y, float xSpeed): GameObject(animationController, x, y, xSpeed)
{
    xSpeedOffset = 0;
    ySpeedOffset = 0;
}

void CloudLayer::moveLayer()
{
    // Wrap clouds around the screen to avoid drifting off forever
    if(animation != NULL && animation->bitmaps.size() > 0)
    {
        // Use a rough default width if not cached
        const float layerWidth = 1280.0f;
        if(x > layerWidth)
        {
            x = -layerWidth;
        }
        else if(x < -layerWidth)
        {
            x = layerWidth;
        }
    }
}

void CloudLayer::update(int32_t timeDiff)
{
    // Make cloud movement time-based; no wrap-around — clouds are spawned
    // ahead of the camera and cleaned up once behind it (see Scene::cleanupClouds).
    x += xSpeed * (timeDiff / 16.0f);
}