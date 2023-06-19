################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/VSCode/ArduinoProjects/Datasheets/CH32/CH32V307/CH32V307_EVT/Examples/SRC/Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: E:/VSCode/ArduinoProjects/Datasheets/CH32/CH32V307/CH32V307_EVT/Examples/SRC/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\ETH\NetLib" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\ETH\WebServer\HTTP" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\SRC\Core" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\SRC\Debug" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\SRC\Peripheral\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\ETH\WebServer\User" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

