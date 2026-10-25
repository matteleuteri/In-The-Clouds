#include "headers/Camera.h"

Camera::Camera(GameObject* following, int width, int height): following(following), width(width), height(height)
{
    x = 0;
    y = 0;
    speed = 0.0f;
}

void Camera::update(int32_t timeElapsed)
{
    (void)timeElapsed;
    // Keep camera fixed to avoid shaking with existing draw logic
    x = 0.0f;
    y = 0.0f;
}