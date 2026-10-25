#ifndef _CAMERA
#define _CAMERA

#include "GameObject.h"
#include <stdint.h>

class Camera 
{
public:
    float x;
    float y;
    int width;
    int height;
    float speed;
    GameObject* following;
    Camera(GameObject* following, int width, int height);
    void update(int32_t timeElapsed);
};

#endif