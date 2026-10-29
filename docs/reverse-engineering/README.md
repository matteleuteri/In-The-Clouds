# In-The-Clouds Reverse Engineering Analysis

Analysis of the compiled `In-The-Clouds.exe` binary.

## Binary Information

- **File:** `build/In-The-Clouds.exe`
- **Format:** PE32+ executable (GUI) x86-64, for MS Windows
- **Architecture:** x86-64
- **Sections:** .text, .rdata, .data, .pdata, _RDATA, .rsrc, .reloc
- **Assets:** Embedded as RCDATA resources in .rsrc section

## Architecture Overview

The game is a 2D platformer built with:
- **Win32 API** - Window management and input
- **Direct2D** - 2D rendering
- **DirectWrite** - Text rendering
- **WIC (Windows Imaging Component)** - Image loading from embedded resources

## Source Code Mapping

The binary was compiled from the source in `code/`:
- `Winmain.cpp` - Entry point, resource loading, game loop
- `Scene.cpp` - World state, collision detection, rendering
- `Player.cpp` - Player physics and movement
- `WorldChunk.cpp` - Moving platforms
- `Animation*.cpp` - Animation system
- `Background.cpp`, `CloudLayer.cpp` - Background elements
- `input/JumpButton.cpp` - Input handling

## Key Components

### Game Loop
Located in `wWinMain()`, the main loop runs at ~60 FPS with frame limiting. It processes messages, updates game state via `Scene::updateState()`, and renders via `Scene::renderState()`.

### Asset Loading
Assets are embedded as RCDATA resources (compiled via `assets.rc`) and loaded through `LoadBitmapFromResource()` using WIC. Resource names include:
- Player: `PLAYER2_IDLE_01-03`, `PLAYER2_JUMP_01-04`
- Platforms: `WORLDCHUNK_1_1-2`, `WORLDCHUNK_2_1-2`
- Background: `BACKGROUND`
- Clouds: `CLOUDLAYER_1_1-3`, `CLOUDLAYER_2_1-3`

### Physics
- Time-based movement using `GetTickCount()` delta time
- Gravity: constant acceleration `ySpeed += 0.002f * timeElapsed`
- Frame limiting: 16ms target frame time

### Collision System
- Platform collision detection in `Scene::checkPlatformCollision()`
- Land-on detection when falling onto platforms
- Edge detection to trigger `fallOff()`
- Coyote time support for edge-walkoff grace period

## Notes

- Full disassembly/decompilation would require reverse engineering tools like Ghidra, IDA Pro, or Binary Ninja
- REA analysis requires provider configuration (Ghidra/Hopper/IDA/Kuna) which are not currently set up
- The binary contains debug symbols in some cases but compiled with optimizations possible
