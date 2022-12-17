
#python 
esptool.py --chip esp32s2 --port COM4 --baud 1000000 write_flash -z 0x0 FIRMWARE.bin

pause