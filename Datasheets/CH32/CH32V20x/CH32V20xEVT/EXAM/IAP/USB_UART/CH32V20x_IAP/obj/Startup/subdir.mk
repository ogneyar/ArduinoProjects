################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
E:/VSCode/ArduinoProjects/Datasheets/CH32/CH32V20x/CH32V20xEVT/EXAM/SRC/Startup/startup_ch32v20x_D8W.S 

OBJS += \
./Startup/startup_ch32v20x_D8W.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v20x_D8W.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32v20x_D8W.o: E:/VSCode/ArduinoProjects/Datasheets/CH32/CH32V20x/CH32V20xEVT/EXAM/SRC/Startup/startup_ch32v20x_D8W.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -x assembler -I"E:\VSCode\ArduinoProjects\Datasheets\CH32\CH32V20x\CH32V20xEVT\EXAM\SRC\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

