#ifndef _PAUSEBUTTON
#define _PAUSEBUTTON

#include "ButtonAction.h"

class PauseButton : public ButtonAction
{
public:
    void PauseButton::execute(std::unique_ptr<Scene>& scene);
};

#endif