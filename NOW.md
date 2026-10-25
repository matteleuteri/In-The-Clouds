# NOW.md
**Last updated:** 2026-10-21
**Current state:** main + uncommitted fixes to `Winmain.cpp` / `Winmain.h` / `ISSUES.txt`

## Quick snapshot
- Repo builds cleanly with MSVC 19.32 (VS 2022 Community). `code/build.bat` auto-detects the toolchain and works from cmd/PowerShell/WSL.
- New files: `ISSUES.txt` (22 categorized issues), `AGENTS.md` (agent onboarding), `run.bat` (Windows launcher), `run_game.ps1` (WSL/PowerShell launcher).
- README updated with clearer build/run instructions + WSL caveats.
- Game runs (Direct2D Win32 app). Asset path is now resolved from the executable location, so it can be launched from any working directory.

## Recently fixed (2026-10-21)
- **#1 Missing `.png`** — `"player2_jump_04"` → `"player2_jump_04.png"` (crash risk removed).
- **#2 Ignored asset-load failures** — `loadBitmapVector()` now checks the HRESULT and skips failed frames (logs via `OutputDebugStringA`); `LoadBitmapFromFile()` rejects NULL factory/render target.
- **#3 CWD-dependent assets** — assets path now derived from `GetModuleFileNameW()`/`../assets`, so the game launches from any directory.
- **#4 Mouse-click fall-through** — added the missing `break` after `WM_LBUTTONDOWN`.

Remaining open issues: see `ISSUES.txt` (#5–#22 have not been touched).

## Suggested next steps (in priority order)
1. **Return to idle after jump:** implement proper animation switching (fill in `AnimationController::setAnimation()` or set `player->animation = player->animationController->getAnimation(IDLE)` on landing/completion). Currently jump anim never switches back.
2. **Make motion time-based:** `CloudLayer::update()` moves per-frame (FPS-dependent); also `player->immune` decrements per frame. Use `timeElapsed` consistently (like `WorldChunk::update()`). Clouds also never wrap (`moveLayer()` is empty).
3. **Fix `landOn()` signature semantics:** either use `newY` or remove the param to avoid confusion (grounded Y is 0 by design today).
4. **Camera follow:** implement `Camera::update()` and have it follow the player (matches README todo #8). Fix `drawPlayer()` grounded case if/when camera moves.
5. **Fix non-physical gravity:** `Player::update()` uses cumulative `timeInAir` in the gravity term, giving super-quadratic fall speed.
6. **Wire up `destinationWidth`/`destinationHeight`** in `LoadBitmapFromFile()` — still accepted but unused (left over from issue #2).

## Build/Run quick refs
- Build (WSL): `cmd.exe /c 'code\build.bat'`
- Run (WSL/PowerShell): `powershell.exe -ExecutionPolicy Bypass -File "C:\Users\meleu\Desktop\In-The-Clouds\run_game.ps1"`
- Run (Windows): `run.bat` or double-click `build\In-The-Clouds.exe`

## Git state
- Branch: main (HEAD = e877f4d "More agentic stuff")
- Uncommitted: `ISSUES.txt`, `code/Winmain.cpp`, `code/headers/Winmain.h` (the four fixes above) — not yet committed.
- WSL gh token can be stale; Windows Git Credential Manager has worked for pushes.

## Environment notes
- Windows 11, VS 2022 Community 17.2.6, MSVC 19.32.31332 x64, Windows SDK 10.0.18362.0
- Repo lives at `/mnt/c/Users/meleu/Desktop/In-The-Clouds` (WSL view) = `C:\Users\meleu\Desktop\In-The-Clouds` (Windows)
- Build artifacts in `build/` (ignored). No untracked build outputs committed.
