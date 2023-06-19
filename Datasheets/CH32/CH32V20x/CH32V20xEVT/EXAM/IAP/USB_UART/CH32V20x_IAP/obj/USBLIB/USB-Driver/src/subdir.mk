################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USBLIB/USB-Driver/src/usb_core.c \
../USBLIB/USB-Driver/src/usb_init.c \
../USBLIB/USB-Driver/src/usb_int.c \
../USBLIB/USB-Driver/src/usb_mem.c \
../USBLIB/USB-Driver/src/usb_regs.c \
../USBLIB/USB-Driver/src/usb_sil.c 

OBJS += \
./USBLIB/USB-Driver/src/usb_core.o \
./USBLIB/USB-Driver/src/usb_init.o \
./USBLIB/USB-Driver/src/usb_int.o \
./USBLIB/USB-Driver/src/usb_mem.o \
./USBLIB/USB-Driver/src/usb_regs.o \
./USBLIB/USB-Driver/src/usb_sil.o 

C_DEPS += \
./USBLIB/USB-Driver/src/usb_core.d \
./USBLIB/USB-Driver/src/usb_init.d \
./USBLIB/USB-Driver/src/usb_int.d \
./USBLIB/USB-Driver/src/usb_mem.d \
./USBLIB/USB-Driver/src/usb_regs.d \
./USBLIB/USB-Driver/src/usb_sil.d 


# Each subdirectory must supply rules for building sources it contributes
USBLIB/USB-Driver/src/%.o: ../USBLIB/USB-Driver/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\USBLIB\USB-Driver\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Debug" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Core" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\User" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Peripheral\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\CONFIG" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

