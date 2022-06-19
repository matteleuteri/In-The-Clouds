#ifndef _JUMPBUTTON
#define _JUMPBUTTON

#include "ButtonAction.h"

class JumpButton : public ButtonAction
{
public:
    void JumpButton::execute(std::unique_ptr<Scene>& scene);
};

#endif