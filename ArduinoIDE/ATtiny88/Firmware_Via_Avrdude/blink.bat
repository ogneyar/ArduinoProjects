echo off
cls
make blink
if "%errorlevel%" == "0" (goto :1)
pause
:1