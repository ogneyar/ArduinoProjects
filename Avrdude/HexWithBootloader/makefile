
PROGRAMMER	:= arduino

TARGET_MCU	:= atmega328p

PORT		:= com8
# PORT		:= com12

# BAUD		:= 9600
# BAUD		:= 19200
BAUD		:= 115200
# BAUD		:= 921600

HEX_NAME	:= EEPROM
HEX			:= $(HEX_NAME).hex

all: 
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX):a
	
	

