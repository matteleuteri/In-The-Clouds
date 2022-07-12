#ifndef _CAMERA
#define _CAMERA

#include "GameObject.h"

class Camera 
{
public:
    int x;
    int y;
    int width;
    int height;
    GameObject* following;
    Camera::Camera();
};


#endif