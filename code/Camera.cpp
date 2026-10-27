#include "headers/Camera.h"

Camera::Camera(GameObject* following, int width, int height): following(following), width(width), height(height)
{
    x = 0;
    y = 0;
    speed = 0.0f;
}

void Camera::update(int32_t timeElapsed, float playerWorldCenterX)
{
    (void)timeElapsed;
    if (!following) return;
    float screenW = (float)width;
    float third = screenW / 3.0f;
    float playerScreenX = playerWorldCenterX - x;
    if (playerScreenX < third)
        x = playerWorldCenterX - third;
    else if (playerScreenX > 2.0f * third)
        x = playerWorldCenterX - 2.0f * third;
}