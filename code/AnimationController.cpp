#include "headers/AnimationController.h"

AnimationController::AnimationController(std::map<int, Animation*> animations): animations(animations)
{}

void AnimationController::setAnimation(ANIMATIONTYPE animationType)
{
    auto it = animations.find((int)animationType);
    if(it != animations.end())
    {
        // Caller is responsible for applying the animation to the target
        // GameObject; this method exists for future use.
    }
}