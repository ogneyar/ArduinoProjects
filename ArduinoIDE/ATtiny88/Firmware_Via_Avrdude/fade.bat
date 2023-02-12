echo off
cls
make fade
if "%errorlevel%" == "0" (goto :1)
pause
:1