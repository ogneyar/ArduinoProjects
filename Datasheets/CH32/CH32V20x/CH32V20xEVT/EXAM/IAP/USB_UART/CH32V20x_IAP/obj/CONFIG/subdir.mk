################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONFIG/hw_config.c \
../CONFIG/usb_desc.c \
../CONFIG/usb_endp.c \
../CONFIG/usb_istr.c \
../CONFIG/usb_prop.c \
../CONFIG/usb_pwr.c 

OBJS += \
./CONFIG/hw_config.o \
./CONFIG/usb_desc.o \
./CONFIG/usb_endp.o \
./CONFIG/usb_istr.o \
./CONFIG/usb_prop.o \
./CONFIG/usb_pwr.o 

C_DEPS += \
./CONFIG/hw_config.d \
./CONFIG/usb_desc.d \
./CONFIG/usb_endp.d \
./CONFIG/usb_istr.d \
./CONFIG/usb_prop.d \
./CONFIG/usb_pwr.d 


# Each subdirectory must supply rules for building sources it contributes
CONFIG/%.o: ../CONFIG/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\USBLIB\USB-Driver\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Debug" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Core" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\User" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Peripheral\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\CONFIG" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

