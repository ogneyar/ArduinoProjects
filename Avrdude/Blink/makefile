
# PROGRAMMER	:= usbasp
# TARGET_MCU	:= atmega8
# BAUD 			:= 19200
# PORT			:= usb

PROGRAMMER		:= arduino
TARGET_MCU		:= atmega328p
BAUD 			:= 115200
PORT			:= com8

TARGET_FCPU		:= 16000000

NAME			:= Blink
ELF				:= $(NAME).elf
HEX				:= $(NAME).hex

GXX_TARGET		:= -mmcu=$(TARGET_MCU) -DF_CPU=$(TARGET_FCPU)UL
GXX_FLAGS		:= -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -c

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
	@avrdude -p $(TARGET_MCU) -c $(PROGRAMMER) -b $(BAUD) -P $(PORT) -U flash:w:$(HEX):a
	
	
	
	

