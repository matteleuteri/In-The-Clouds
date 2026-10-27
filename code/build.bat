@echo off
setlocal

rem =========================================================================
rem  In-The-Clouds build script
rem
rem  Compiles the game to build\In-The-Clouds.exe.
rem  Sets up the MSVC environment itself if needed.
rem =========================================================================

rem If cl.exe is already on PATH (e.g. inside a Developer Command Prompt),
rem skip environment setup and go straight to compiling.
where cl >nul 2>nul
if not errorlevel 1 goto :compile

rem --- Find the Visual Studio C++ toolchain --------------------------------

rem Preferred: ask the VS Installer where things are (vswhere).
set "VCVARS="
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" goto :known_paths
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VCVARS=%%i\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCVARS if not exist "%VCVARS%" set "VCVARS="

rem Fallback: well-known install locations.
:known_paths
if defined VCVARS goto :env_ready
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" set "VCVARS=%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCVARS goto :env_ready
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" set "VCVARS=%ProgramFiles%\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCVARS goto :env_ready
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" set "VCVARS=%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCVARS goto :env_ready
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" set "VCVARS=%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
if defined VCVARS goto :env_ready

echo.
echo ERROR: Could not find a C++ toolchain ^(cl.exe^).
echo.
echo Install Visual Studio or the Build Tools with the workload
echo "Desktop development with C++" via the Visual Studio Installer,
echo then run this script again.
echo.
exit /b 1

:env_ready
echo Setting up MSVC environment:
echo   %VCVARS%
call "%VCVARS%" x64 >nul
if errorlevel 1 goto :env_failed

rem --- Compile -------------------------------------------------------------

:compile
set "ROOT=%~dp0.."
if not exist "%ROOT%\build" mkdir "%ROOT%\build"
pushd "%ROOT%\build"

set compilerFlags=-EHsc -W4 -wd4100 -Z7 -std:c++17 /Fe"In-The-Clouds.exe"
set linkerFlags=-link -INCREMENTAL:NO -DEBUG:FULL

echo.
echo Compiling...
cl %compilerFlags% ..\code\*.cpp ..\code\background\*.cpp ..\code\input\*.cpp %linkerFlags% user32.lib d2d1.lib Ole32.lib Shlwapi.lib Dwrite.lib
set "BUILD_RESULT=%errorlevel%"

popd

if not "%BUILD_RESULT%"=="0" goto :build_failed

echo.
echo BUILD OK: build\In-The-Clouds.exe
exit /b 0

:env_failed
echo ERROR: Failed to initialize the MSVC environment.
exit /b 1

:build_failed
echo.
echo BUILD FAILED — see errors above.
exit /b 1
