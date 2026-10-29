# Binary Analysis

## File Structure

```
In-The-Clouds.exe (PE32+ x86-64)
├── .text         - Executable code
├── .rdata        - Read-only data (strings, constants)
├── .data         - Initialized data
├── .pdata        - Exception handling data (x64)
├── _RDATA        - Read-only data
├── .rsrc         - Resources (embedded assets)
└── .reloc        - Relocation table
```

## Imported Libraries

Based on the codebase:
- `user32.lib` - Win32 API (window creation, messages)
- `d2d1.lib` - Direct2D rendering
- `Ole32.lib` - COM initialization
- `Shlwapi.lib` - Shell utilities
- `Dwrite.lib` - DirectWrite text

## Resource Section

The `.rsrc` section contains the embedded PNG assets as RCDATA resources. Resource IDs match the names used in code:
- PLAYER2_IDLE_01 through PLAYER2_IDLE_03
- PLAYER2_JUMP_01 through PLAYER2_JUMP_04
- WORLDCHUNK_1_1, WORLDCHUNK_1_2, WORLDCHUNK_2_1, WORLDCHUNK_2_2
- BACKGROUND
- CLOUDLAYER_1_1, CLOUDLAYER_1_2, CLOUDLAYER_1_3
- CLOUDLAYER_2_1, CLOUDLAYER_2_2, CLOUDLAYER_2_3

## String References

Key strings found in the binary would include:
- Window class name: "In The Clouds"
- Font: "Gabriola"
- Debug messages via OutputDebugStringA
- Log messages

## Entry Point

The entry point is `wWinMain` (Unicode WinMain) as defined in Winmain.cpp.

## Game Constants (from source)

- Window resolution: CW_USEDEFAULT initially, but rendering uses client rect
- Player start position: (600, 60)
- Target FPS: ~60 (16ms frame cap)
- Gravity factor: `0.002f * timeElapsed * 100.0f` in air
- Jump velocity: `-1.3f`
- Player movement speed: `±0.5f`
