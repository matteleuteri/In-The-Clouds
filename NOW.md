# NOW.md
**Last updated:** 2026-10-19
**Current state:** main (c5c44fc "Add agentic assistance") — pushed to origin/main

## Quick snapshot
- Repo builds cleanly with MSVC 19.32 (VS 2022 Community). `code/build.bat` auto-detects the toolchain and works from cmd/PowerShell/WSL.
- New files: `ISSUES.txt` (22 categorized issues), `AGENTS.md` (agent onboarding), `run.bat` (Windows launcher), `run_game.ps1` (WSL/PowerShell launcher).
- README updated with clearer build/run instructions + WSL caveats.
- Game runs (Direct2D Win32 app). Must start with working dir = `build\` (asset path `../assets/`).

## Critical known issue (highest priority)
- **CRASH RISK:** `code/Winmain.cpp:182` — `"player2_jump_04"` missing `.png` extension → `LoadBitmapFromFile` fails, uninitialized `ID2D1Bitmap*` pushed into animation vector. Rendering that frame will crash. (ISSUES.txt #1)

## Suggested next steps (in priority order)
1. **Fix the crash bug (easy):** in `code/Winmain.cpp`, line ~182 change `"player2_jump_04"` → `"player2_jump_04.png"`. Rebuild and test.
2. **Add HRESULT checks:** harden `LoadBitmapFromFile()` and `createResources()` so failed asset loads don't produce garbage pointers; log/fail gracefully.
3. **Fix message fall-through:** in `WindowProc()`, add `break` after the empty `WM_LBUTTONDOWN` case (currently falls through to `WM_KEYDOWN`).
4. **Return to idle after jump:** implement proper animation switching (fill in `AnimationController::setAnimation()` or set `player->animation = player->animationController->getAnimation(IDLE)` on landing/completion). Currently jump anim never switches back.
5. **Make motion time-based:** `CloudLayer::update()` moves per-frame (FPS-dependent); also `player->immune` decrements per frame. Use `timeElapsed` consistently (like `WorldChunk::update()`).
6. **Camera follow:** implement `Camera::update()` and have it follow the player (matches README todo #8). Fix `drawPlayer()` grounded case if/when camera moves.
7. **Fix `landOn()` signature semantics:** either use `newY` or remove the param to avoid confusion (grounded Y is 0 by design today).

## Build/Run quick refs
- Build (WSL): `cmd.exe /c 'code\build.bat'`
- Run (WSL/PowerShell): `powershell.exe -ExecutionPolicy Bypass -File "C:\Users\meleu\Desktop\In-The-Clouds\run_game.ps1"`
- Run (Windows): `run.bat` or double-click `build\In-The-Clouds.exe`

## Git state
- Branch: main (ahead of origin by 1 commit: c5c44fc "Add agentic assistance")
- Pushed successfully (Windows Git Credential Manager used; WSL gh token can be stale)

## Environment notes
- Windows 11, VS 2022 Community 17.2.6, MSVC 19.32.31332 x64, Windows SDK 10.0.18362.0
- Repo lives at `/mnt/c/Users/meleu/Desktop/In-The-Clouds` (WSL view) = `C:\Users\meleu\Desktop\In-The-Clouds` (Windows)
- Build artifacts in `build/` (ignored). No untracked build outputs committed.
