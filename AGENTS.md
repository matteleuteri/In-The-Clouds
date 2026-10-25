# Agent Guidelines

This file provides guidance for AI coding agents working on this project ("In-The-Clouds").

## Project Overview

This is a 2D platformer written in C++ (C++17) using **Win32 + Direct2D + DirectWrite + WIC**. The codebase is small, all source lives under `code/` with headers in `code/headers/`, assets in `assets/`, and build output in `build/` (ignored).

Key facts:
- **Build:** Windows-only, built via MSVC (`cl.exe`). `code/build.bat` automatically finds and sets up the MSVC environment (vswhere + fallbacks for VS 2022/2019 Build Tools). Works from normal Command Prompt/PowerShell/WSL.
- **Runtime:** Must be started with working directory = `build\` (game loads `../assets/`). Use `run_game.ps1` from WSL/PowerShell, or `run.bat`/double-click exe from Windows.
- **Game loop:** `Winmain.cpp::wWinMain()` sets up D2D/DWrite/WIC, hardcodes asset loading, creates a `Scene`, then loops: pump messages → `scene->updateState()` → `scene->renderState()`. Timing uses `GetTickCount()`, no frame limiter, no vsync.
- **Architecture:** `Scene` owns game state (Player, WorldChunks, Backgrounds, CloudLayers, Camera). `GameObject` is base; animations via `Animation` + `AnimationController`. Input: `JumpButton` (command pattern) wired to `VK_UP`.

## Build Commands

**Windows (cmd/PowerShell/File Explorer):**
```bat
code\build.bat
```

**WSL (bash):**
```sh
cmd.exe /c 'code\build.bat'
```

Successful build creates `build\In-The-Clouds.exe` and `.pdb`.

## Run Commands

**Windows (recommended):** double-click `build\In-The-Clouds.exe` OR `run.bat`

**WSL / PowerShell (reliable, sets correct cwd):**
```sh
powershell.exe -ExecutionPolicy Bypass -File "C:\Users\meleu\Desktop\In-The-Clouds\run_game.ps1"
```

**Controls:** Left/Right arrows = move, Up arrow = jump, Close window = quit.

## Known Issues (Critical)

See `ISSUES.txt` for the full list (22 items). Items **#1–#4** have been fixed as of 2026-10-21:

1. **[FIXED] CRASH RISK: `Winmain.cpp:182`** — added `.png` extension to `"player2_jump_04"`.
2. **[FIXED] Asset load failures ignored** — `loadBitmapVector()` now checks HRESULTs and skips failed frames (logs via `OutputDebugStringA`); `LoadBitmapFromFile()` guards against NULL factory/render target.
3. **[FIXED] CWD-dependent assets** — asset path is now derived from `GetModuleFileNameW()`/`../assets`, so the game can launch from any working directory.
4. **[FIXED] Mouse click falls through** to `WM_KEYDOWN` — added missing `break` in `WindowProc()`.

The most important remaining ones:
5. **Player never returns to idle** after jumping (`AnimationController::setAnimation()` stub; `Player::jump()` only switches to jump anim).
6. **Frame-rate dependent motion** for clouds and `immune` timer (uses per-frame increments; `WorldChunk` correctly uses `timeElapsed`).
7. **`landOn()` ignores `newY`** parameter (hardcodes Y=0) — the grounded coordinate system is a bit of a hack (chunk-relative coords at draw time).

## Code Style & Conventions

- **Language:** C++17, MSVC-specific flags (`/EHsc`, `/W4`, `-wd4100`). The build disables warning C4100 (unused parameters). Some header declarations use MSVC-isms (`void Scene::method()` inside class body) — don't change this unless you intend to port away from MSVC.
- **Naming:** PascalCase for classes (`Scene`, `Player`), camelCase-ish for members (`xSpeed`, `timeInAir`), follows existing style.
- **Includes:** headers use `#ifndef` guards (`_SCENE`, etc.). Winmain has globals declared in `headers/Winmain.h` (single-TU pattern) — be careful adding includes that might create ODR issues.
- **Memory:** Raw `new` everywhere, no RAII cleanup on exit, COM objects not explicitly released — this is a learning project; match existing patterns unless you're doing a cleanup pass.
- **Timing:** `GetTickCount()` (ms). Delta time passed around as `int32_t` milliseconds.
- **DirectX:** Direct2D 1.0 APIs used directly. No error handling on HRESULTs in many places (see issue #15).

## Important Gotchas

- **Do not run `.bat` files directly under bash** — they must go through `cmd.exe` (see Build Commands above). If you see `@echo: command not found`, you made this mistake.
- **Pushes from WSL may fail with token/auth errors** (GitHub no longer accepts password auth; the gh CLI token can be stale). Windows Git's Credential Manager often works; use `cmd.exe /c 'cd /d ... && git push origin main'` as a fallback if needed.
- **Dead code exists:** `JsonParser.cpp/h`, `Token.cpp/h`, `assets/ResourceTree.json` are unused (commented-out call site). Don't assume they're functional; the parser has known bugs (hard-coded paths, `sizeof` on decayed array, missing definitions).
- **Assets list is duplicated:** some chunk definitions are copy-pasted (chunk3 reuses chunk2 textures). Keep in sync only if you resurrect the JSON-driven loader.

## Suggested First Fixes (Low-hanging fruit)

If asked to fix bugs, prioritize:
1. Fix the missing `.png` extension in `Winmain.cpp:182` (`"player2_jump_04"`) — easy correctness fix with immediate crash-prevention benefit.
2. Add `break` after `WM_LBUTTONDOWN` case in `WindowProc()` (prevents fall-through).
3. Add basic HRESULT checks in `LoadBitmapFromFile()`/`createResources()` and log or bail safely.
4. Make cloud movement time-based (or at least document/normalize), and have clouds wrap around.

## When Working With This Repo

- **Respect existing structure:** match file organization (`code/*.cpp`, `code/headers/*.h`, `code/background/`, `code/input/`).
- **Keep build working:** after changes, rebuild with `code/build.bat` (via cmd.exe in WSL or Windows) and ensure no new linker errors.
- **Don't commit build artifacts:** `build/`, `*.obj`, `*.pdb`, `*.exe` are in `.gitignore`. `ISSUES.txt`, `AGENTS.md`, `NOW.md`, `run*.bat`, `run*.ps1` are fine to commit.
- **Test by running:** the game is a visual app (Direct2D). Launch via the run helpers (correct cwd) and verify it doesn't crash immediately on startup.

## Notes From Recent Agent Work

- Agent reviewed the full codebase (medium thoroughness) and produced `ISSUES.txt` with categorized findings.
- Agent made `code/build.bat` self-contained (auto-detects MSVC), added `run.bat`/`run_game.ps1` for easier launching, and updated `README.md` with clear build/run instructions + WSL caveats.
- The executable builds cleanly with MSVC 19.32 (VS 2022). No compilation warnings introduced by the script changes.
