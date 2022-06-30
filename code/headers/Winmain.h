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
#include "ButtonAction.h"
#include "JumpButton.h"

static bool isRunning;
std::filesystem::path p;
std::unique_ptr<Scene> scene;
ID2D1HwndRenderTarget* renderTarget;
ID2D1SolidColorBrush* brushes[3];

ButtonAction *up_Button;

IDWriteFactory *pDWriteFactory_;
IDWriteTextFormat *pTextFormat_;
