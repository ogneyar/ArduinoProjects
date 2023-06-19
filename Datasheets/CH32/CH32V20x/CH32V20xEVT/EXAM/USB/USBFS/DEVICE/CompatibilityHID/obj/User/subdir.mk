################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/ch32v20x_usbfs_device.c \
../User/main.c \
../User/system_ch32v20x.c \
../User/usb_desc.c \
../User/usbd_compatibility_hid.c 

OBJS += \
./User/ch32v20x_it.o \
./User/ch32v20x_usbfs_device.o \
./User/main.o \
./User/system_ch32v20x.o \
./User/usb_desc.o \
./User/usbd_compatibility_hid.o 

C_DEPS += \
./User/ch32v20x_it.d \
./User/ch32v20x_usbfs_device.d \
./User/main.d \
./User/system_ch32v20x.d \
./User/usb_desc.d \
./User/usbd_compatibility_hid.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Debug" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Core" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\USB\USBFS\DEVICE\CompatibilityHID\User" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

