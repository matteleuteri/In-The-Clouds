#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdint.h>
#include <profileapi.h>
#include <filesystem>
#include <array>
#include <dwrite.h>

#include "Scene.h"
#include "JsonParser.h"
#include "ButtonAction.h"
#include "JumpButton.h"

static bool isRunning;
std::filesystem::path p;
std::unique_ptr<Scene> scene;
ID2D1HwndRenderTarget* renderTarget;

ButtonAction *up_Button;

IDWriteFactory *pDWriteFactory_;
IDWriteTextFormat *pTextFormat_;
