
PROGRAMMER_INO	:= arduino
PROGRAMMER_ASP	:= usbasp
PROGRAMMER	:= $(PROGRAMMER_INO)

PORT := com5

BOUDRATE := 115200

TARGET_MCU	:= atmega328p

HEX	:= GyverControl_1.6.ino.hex
HEX_WB	:= GyverControl_1.6.ino.with_bootloader.hex

all:
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -b $(BOUDRATE) -U flash:w:$(HEX):a -P $(PORT)
	
ino:
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -b $(BOUDRATE) -U flash:w:$(HEX):a -P $(PORT)

inowb:
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -b $(BOUDRATE) -U flash:w:$(HEX_WB):a -P $(PORT)

asp:
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER_ASP) -b $(BOUDRATE) -U flash:w:$(HEX):a -P $(PORT)
	
aspwb:
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER_ASP) -b $(BOUDRATE) -U flash:w:$(HEX_WB):a -P $(PORT)

# avrdude -p atmega328p -c arduino -P com5 -b 115200 -U flash:w:GyverControl_1.6.ino.hex:a
