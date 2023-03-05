
# PROGRAMMER	:= avrisp -P com6
PROGRAMMER	:= usbasp

TARGET_MCU	:= atmega8
# TARGET_MCU	:= attiny13
# TARGET_MCU	:= m328pb -B 125kHz
TARGET_FCPU	:= 16000000

OUTPUT_NAME	:= AVR_makefile
HEX_NAME	:= firmware_1_3
ELF			:= $(OUTPUT_NAME).elf
HEX			:= $(HEX_NAME).hex

GXX_TARGET	:= -mmcu=$(TARGET_MCU) -DF_CPU=$(TARGET_FCPU)UL
GXX_FLAGS	:= -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -c

all: upload
	@avr-size --format=berkeley $(ELF)
	@del main.o $(ELF) $(LSS) $(MAP)
	@echo Finish: $@

main.o: main.c makefile
	@avr-gcc $(GXX_FLAGS) $(GXX_TARGET) -o main.o main.c
	@echo Building: $@
	
$(ELF): main.o
	@avr-gcc -mmcu=$(TARGET_MCU) $(GXX_TARGET) -o $(ELF) main.o
	@echo Linking: $@
	
$(HEX): $(ELF)
	@avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $(ELF) $(HEX)
	@echo Create: $@
	
upload: $(HEX)
	@echo Program $(TARGET_MCU)
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -b 19200 -U flash:w:$(HEX):a
	
#avrdude.exe -p m328pb -B 125kHz -c usbasp -P usb -U calibration:r:calibration.hex:r
#avrdude.exe -p m328pb -B 125kHz -c usbasp -P usb -U flash:w:firmware_1_3.hex:a

