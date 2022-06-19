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
#include "input/headers/ButtonAction.h"
#include "input/headers/JumpButton.h"

static bool isRunning;
std::filesystem::path p;
std::unique_ptr<Scene> scene;
ID2D1HwndRenderTarget* renderTarget;
ID2D1SolidColorBrush* brushes[3];

ID2D1Bitmap *playerBitmap_idle_01;
ID2D1Bitmap *playerBitmap_idle_02;
ID2D1Bitmap *playerBitmap_idle_03;
ID2D1Bitmap *BLayer1_1;
ID2D1Bitmap *chunk_bm_1;
ID2D1Bitmap *chunk_bm_2;

ButtonAction *up_Button;

IDWriteFactory *pDWriteFactory_;
IDWriteTextFormat *pTextFormat_;