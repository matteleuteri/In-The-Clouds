@echo off
setlocal
set "ROOT=%~dp0"
cd /d "%ROOT%\build"
start "" "In-The-Clouds.exe"
exit /b 0
