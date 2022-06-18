@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set compilerFlags=-EHsc -W4 -wd4100 -Z7 -std:c++17 /Fe"In-The-Clouds.exe"

set linkerFlags=-link -INCREMENTAL:NO -DEBUG:FULL

cl %compilerFlags% ..\code\*.cpp ..\code\background\*.cpp %linkerFlags% user32.lib d2d1.lib Ole32.lib Shlwapi.lib Dwrite.lib

popd