#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>
#include <array>
#include <cstdio>
#include <dwrite.h>

#include "Scene.h"
#include "JsonParser.h"
#include "ButtonAction.h"
#include "JumpButton.h"

static bool isRunning;
std::unique_ptr<Scene> scene;
ID2D1HwndRenderTarget* renderTarget;

ButtonAction *up_Button;

IDWriteFactory *pDWriteFactory_;
IDWriteTextFormat *pTextFormat_;
