# In-The-Clouds

A 2D platformer written in C++ using Win32 and Direct2D. This is a game I am
making to learn C++ and game development.

## Requirements

- Windows 10/11
- **Visual Studio 2022** (the free Community edition is fine) **or** the
  standalone *Build Tools for Visual Studio 2022*, installed with the
  workload **"Desktop development with C++"** — this provides `cl.exe`
  (the MSVC compiler) and the Windows SDK.

You do **not** need to open a "Developer Command Prompt" — the build script
sets up the compiler environment itself.

## How to build

Either:

1. **Double-click `code\build.bat`** in File Explorer, or
2. run it from any normal Command Prompt / PowerShell:

   ```bat
   C:\Users\meleu\Desktop\In-The-Clouds\code\build.bat
   ```

   From WSL (run from this repository's directory — note the backslash):

   ```sh
   cmd.exe /c 'code\build.bat'
   ```

   > Do **not** run `./code/build.bat` in the shell — `.bat` files are Windows
   > `cmd.exe` scripts and will only produce errors under bash.

The script locates the MSVC toolchain (via `vswhere`, with fallbacks), loads
the compiler environment, compiles every source file, and links the game.
A successful run ends with:

```
BUILD OK: build\In-The-Clouds.exe
```

## How to start the game

**Double-click `build\In-The-Clouds.exe`** — or, from a terminal:

```bat
cd build
In-The-Clouds.exe
```

> The game finds its sprites relative to the executable's own location
> (`build\..\assets\`), so you can now launch it from any working directory.
> If you move the `.exe` out of `build\`, keep it next to an `assets\` folder.

## Controls

| Key        | Action |
|------------|--------|
| Left / Right arrows | move |
| Up arrow   | jump |
| Close window | quit |

## Project layout

```
code\
  Winmain.cpp        entry point: window, game loop, asset loading
  Scene.cpp          the world: level layout, physics, collision, rendering
  Player.cpp         the player: jump, fall, chunk-relative coordinates
  WorldChunk.cpp     moving platforms
  Animation*.cpp     frame-based animation + controller
  Camera.cpp         camera (not active yet)
  JsonParser.cpp     unused JSON loader (see ISSUES.txt)
  headers\           class declarations
  background\        Background and CloudLayer (parallax scrolling)
  input\             input commands (JumpButton, PauseButton)
  build.bat          build script (see above)
assets\              sprites, backgrounds, ResourceTree.json
build\               build output — created by build.bat, not committed
ISSUES.txt           known issues found during a full code review
```

