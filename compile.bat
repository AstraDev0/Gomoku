@echo off

set ARCH=x64

if "%1" == "" goto release
if "%1" == "release" goto release
if "%1" == "debug" goto debug
if "%1" == "clean" goto clean

@echo Usage: make.bat [release|debug|clean]
goto end

:release
cmake -B build-%ARCH% -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR_PLATFORM=%ARCH%
cmake --build build-%ARCH% --config Release
goto end

:debug
cmake -B build-%ARCH% -DCMAKE_BUILD_TYPE=Debug -DCMAKE_GENERATOR_PLATFORM=%ARCH%
cmake --build build-%ARCH% --config Debug
goto end

:clean
rmdir /s /q build-%ARCH%
del /q /f *.exe
del /q /f *.pdb
del /q /f *.log

:end
