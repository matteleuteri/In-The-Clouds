#ifndef _ANIMATIONCONTROLLER
#define _ANIMATIONCONTROLLER

#include "Animation.h"
#include <map>

enum ANIMATIONTYPE
{
    IDLE = 0,
    JUMP = 1,
    CRUMBLE
};

class AnimationController
{
public:
    std::map<int, Animation*> animations;
    AnimationController(std::map<int, Animation*> animations);
    void setAnimation(ANIMATIONTYPE animationType);
};

#endif