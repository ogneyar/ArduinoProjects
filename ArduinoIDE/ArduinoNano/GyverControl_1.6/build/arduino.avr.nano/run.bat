@echo off

rem загрузка прошивки в arduino Nano

avrdude -p atmega328p -c arduino -P com5 -b 115200 -U flash:w:GyverControl_1.6.ino.hex:a

echo =========================================

@pause
