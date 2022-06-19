#ifndef _BUTTONACTION
#define _BUTTONACTION

#include "../../headers/Scene.h"

class ButtonAction
{
public:
    virtual void execute(std::unique_ptr<Scene>& scene) = 0;
};

#endif