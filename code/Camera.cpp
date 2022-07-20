#include "headers/Camera.h"

Camera::Camera(GameObject* following, int width, int height): following(following), width(width), height(height)
{
    x = 0;
    y = 0;
}