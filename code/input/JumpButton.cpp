#include "headers/JumpButton.h"

void JumpButton::execute(std::unique_ptr<Scene>& scene)
{
    scene->player->jump();
    scene->player->animation = scene->player->jumpAnimation;// only for a short time
    scene->player->immune = 100;
    scene->player->x = scene->player->x + scene->player->chunkCurrentlyOn->x - scene->player->width;
    scene->player->y = scene->player->y + scene->player->chunkCurrentlyOn->y - scene->player->height;
    scene->player->isInAir = true;
    scene->player->inAirStartTime = GetTickCount();
}
