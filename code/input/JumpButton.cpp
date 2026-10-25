#include "../headers/JumpButton.h"

void JumpButton::execute(std::unique_ptr<Scene>& scene)
{
    if(scene->player != NULL && !scene->player->isInAir)
    {
        scene->player->jump();
    }
}
