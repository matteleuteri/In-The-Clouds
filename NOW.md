# NOW.md
**Last updated:** 2026-10-25
**Current state:** main + uncommitted fixes

## Quick snapshot
- Repo builds cleanly with MSVC 19.32 (VS 2022 Community). `code/build.bat` auto-detects the toolchain and works from cmd/PowerShell/WSL.
- Fixed issues #1-#12; remaining open: #13-#18, #20-#22 (#19 fixed).
- Game runs (Direct2D Win32 app). Asset path resolved from executable location.

## Recently fixed (2026-10-21 to 2026-10-25)
- **#1-#4**: crash risks, asset loading hardening, exe-relative assets, WM_LBUTTONDOWN fall-through
- **#5**: player returns to idle on land/fall; animation switching improved
- **#6**: time-based cloud movement with wrap-around; immune timer normalized by timeElapsed
- **#7**: gravity made time-based/constant-accel style
- **#8**: landOn uses newY; timeInAir reset
- **#9**: removed class-qualified MSVC declarations in Player.h
- **#10**: camera follows player with update/lerp; drawing applies camera transform
- **#11**: chunk 3 uses correct textures
- **#12**: fixed -0.0f typo

## Open issues
See `ISSUES.txt` (#13-#18, #20-#22).

## Build/Run quick refs
- Build (WSL): `cmd.exe /c 'code\build.bat'`
- Run (WSL/PowerShell): `powershell.exe -ExecutionPolicy Bypass -File "C:\Users\meleu\Desktop\In-The-Clouds\run_game.ps1"`
- Run (Windows): `run.bat` or double-click `build\In-The-Clouds.exe`

## Git state
- Branch: main
- Uncommitted: fixes for #5-#12 and markdown updates

## Environment notes
- Windows 11, VS 2022 Community 17.2.6, MSVC 19.32.31332 x64, Windows SDK 10.0.18362.0
- Repo lives at `/mnt/c/Users/meleu/Desktop/In-The-Clouds`
- Build artifacts in `build/` (ignored)
