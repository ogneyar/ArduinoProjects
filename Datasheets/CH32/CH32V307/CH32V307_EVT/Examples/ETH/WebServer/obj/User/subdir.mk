################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\ETH\NetLib" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\ETH\WebServer\HTTP" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\SRC\Core" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\SRC\Debug" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\SRC\Peripheral\inc" -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V307\CH32V307_EVT\Examples\ETH\WebServer\User" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

