# NOW.md
**Last updated:** 2026-10-27
**Current state:** main + all changes committed and pushed

## Quick snapshot
- Repo builds cleanly with MSVC 19.32 (VS 2022 Community). `code/build.bat` auto-detects the toolchain and works from cmd/PowerShell/WSL.
- Fixed issues #1-#13; remaining open: #14-#18, #20-#22 (#19 fixed).
- Game runs (Direct2D Win32 app). Asset path resolved from executable location.

## Recently fixed (2026-10-21 to 2026-10-27)
- **#1-#4**: crash risks, asset loading hardening, exe-relative assets, WM_LBUTTONDOWN fall-through
- **#5**: player returns to idle on land/fall; animation switching improved
- **#6**: time-based cloud movement with wrap-around; immune timer normalized by timeElapsed
- **#7**: gravity made constant-acceleration (ySpeed += 0.002f * timeElapsed)
- **#8**: landOn uses newY; timeInAir reset
- **#9**: removed class-qualified MSVC declarations in Player.h
- **#10**: deadzone camera keeps player in middle third; drawing applies camera transform
- **#11**: chunk 3 uses correct textures
- **#12**: fixed -0.0f typo
- **#13**: frame limiter caps main loop at ~60 FPS (16 ms sleep)

## New features (2026-10-26 to 2026-10-27)
- **Down-arrow fall-through** — VK_DOWN while grounded drops through the platform (natural gravity from rest, immune grace period)
- **Deadzone camera** — player stays in middle third; world pans horizontally
- **Tiling background** — background repeats horizontally; 1px tile overlap hides seams
- **Procedural generation** — chunks and clouds spawn ahead of camera, despawn behind; chunks at varying heights
- **Debug logging** — OutputDebugStringA logs player updates and collision events
- **Collision hardening** — landing always checked (even during immune);
  re-landing on the just-fell-off chunk is suppressed while immune (fixes
  wall at platform edge); respawn/cleanup avoid dangling chunk pointers

## Build/Run quick refs
- Build (WSL): `cmd.exe /c 'code\build.bat'`
- Run (WSL/PowerShell): `powershell.exe -ExecutionPolicy Bypass -File "C:\Users\meleu\Desktop\In-The-Clouds\run_game.ps1"`
- Run (Windows): `run.bat` or double-click `build\In-The-Clouds.exe`

## Git state
- Branch: main
- All changes committed

## Environment notes
- Windows 11, VS 2022 Community 17.2.6, MSVC 19.32.31332 x64, Windows SDK 10.0.18362.0
- Repo lives at `/mnt/c/Users/meleu/Desktop/In-The-Clouds`
- Build artifacts in `build/` (ignored)
