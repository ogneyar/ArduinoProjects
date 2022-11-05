
TARGET_MCU_8		:= atmega8
TARGET_MCU_88		:= atmega88

HEX_NAME_8	:= usbasp.atmega8.2011-05-28
HEX_NAME_88	:= usbasp.atmega88.2011-05-28
HEX_NAME_88M := usbasp.atmega88-modify

HEX_8		:= $(HEX_NAME_8).hex
HEX_88		:= $(HEX_NAME_88).hex
HEX_88M		:= $(HEX_NAME_88M).hex
	
a8: 
	@echo Program $(TARGET_MCU_8)
	@avrdude -p $(TARGET_MCU_8) -c usbasp -B 1 -U hfuse:w:0xC9:m -U lfuse:w:0xEF:m
	@avrdude -p $(TARGET_MCU_8) -c usbasp -B 300 -U flash:w:$(HEX_8)
	
a88: 
	@echo Program $(TARGET_MCU_88)
	@avrdude -p $(TARGET_MCU_88) -c usbasp -B 1 -U lfuse:w:0xff:m -U hfuse:w:0xdd:m 
	@avrdude -p $(TARGET_MCU_88) -c usbasp -B 300 -U flash:w:$(HEX_88)
	
a88m: 
	@echo Program $(TARGET_MCU_88)
	@avrdude -p $(TARGET_MCU_88) -c usbasp -B 1 -U lfuse:w:0xff:m -U hfuse:w:0xdd:m 
	@avrdude -p $(TARGET_MCU_88) -c usbasp -B 300 -U flash:w:$(HEX_88M)