#ifndef _ANIMATIONCONTROLLER
#define _ANIMATIONCONTROLLER

#include "Animation.h"
#include <map>

enum ANIMATIONTYPE
{
    JUMP,
    CRUMBLE
};

class AnimationController
{
public:
    std::map<int, Animation*> animations;
    AnimationController::AnimationController(std::map<int, Animation*> animations);
    void AnimationController::setAnimation(ANIMATIONTYPE animationType);
};

#endif