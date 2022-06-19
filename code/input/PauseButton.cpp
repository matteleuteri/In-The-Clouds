#include "headers/PauseButton.h"

void PauseButton::execute(std::unique_ptr<Scene>& scene)
{
    scene->player->isActive = !scene->player->isActive;
}
