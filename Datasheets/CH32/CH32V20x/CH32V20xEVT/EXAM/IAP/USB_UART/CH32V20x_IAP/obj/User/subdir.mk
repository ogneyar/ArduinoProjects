################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/ch32v20x_usbotg_device.c \
../User/flash.c \
../User/iap.c \
../User/main.c \
../User/system_ch32v20x.c 

OBJS += \
./User/ch32v20x_it.o \
./User/ch32v20x_usbotg_device.o \
./User/flash.o \
./User/iap.o \
./User/main.o \
./User/system_ch32v20x.o 

C_DEPS += \
./User/ch32v20x_it.d \
./User/ch32v20x_usbotg_device.d \
./User/flash.d \
./User/iap.d \
./User/main.d \
./User/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\USBLIB\USB-Driver\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Debug" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Core" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\User" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Peripheral\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\IAP\USB_UART\CH32V20x_IAP\CONFIG" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

