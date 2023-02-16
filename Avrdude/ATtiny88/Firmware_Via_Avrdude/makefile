
PROGRAMMER	:= usbasp

TARGET_MCU	:= attiny88

# TARGET_FCPU	:= 16000000

# BAUD		:= -b 19200

NAME		:= Blink
NAME2		:= Fade
HEX			:= $(NAME).hex
HEX2		:= $(NAME2).hex


all: 
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):a	
	@echo Finish: $@
	

blink: 
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):a	
	@echo Finish: $@
	

fade: 
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -U flash:w:$(HEX2):a	
	@echo Finish: $@
	

# avrdude -p attiny88 -c usbasp -U flash:w:Blink.hex:a	
