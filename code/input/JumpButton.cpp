#include "headers/JumpButton.h"

void JumpButton::execute(std::unique_ptr<Scene>& scene)
{
    scene->player->jump();
    // scene->player->switchAnimation();
}
