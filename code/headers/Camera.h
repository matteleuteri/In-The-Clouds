#ifndef _CAMERA
#define _CAMERA

#include "GameObject.h"

class Camera 
{
public:
    float x;
    float y;
    int width;
    int height;
    float speed;
    GameObject* following;
    Camera::Camera(GameObject* following, int width, int height);
};

#endif