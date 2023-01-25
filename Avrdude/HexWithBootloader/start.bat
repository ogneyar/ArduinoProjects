echo off
cls
make
if "%errorlevel%" == "0" (goto :1)
pause
:1