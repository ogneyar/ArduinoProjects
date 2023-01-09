@echo off

rem загрузка прошивки в arduino Nano

set /p comPort=Input number com port: 

avrdude -p atmega328p -c arduino -P com%comPort% -b 115200 -U flash:w:GyverControl_1.6.ino.hex:a

echo =========================================

@pause
