#ifndef _ANIMATIONCONTROLLER
#define _ANIMATIONCONTROLLER

#include "Animation.h"

enum ANIMATIONTYPE
{
    JUMP,
    CRUMBLE
};

class AnimationController
{
public:
    std::vector<Animation*> animations;
    AnimationController::AnimationController(std::vector<Animation*> animations);
    void AnimationController::setAnimation(ANIMATIONTYPE animationType);
};

#endif