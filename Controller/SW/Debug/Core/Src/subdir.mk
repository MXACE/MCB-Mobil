################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CMDHandler.c \
../Core/Src/COM.c \
../Core/Src/bmg250.c \
../Core/Src/gfx.c \
../Core/Src/joystick.c \
../Core/Src/lora.c \
../Core/Src/main.c \
../Core/Src/screen.c \
../Core/Src/ssd1351.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/CMDHandler.o \
./Core/Src/COM.o \
./Core/Src/bmg250.o \
./Core/Src/gfx.o \
./Core/Src/joystick.o \
./Core/Src/lora.o \
./Core/Src/main.o \
./Core/Src/screen.o \
./Core/Src/ssd1351.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/CMDHandler.d \
./Core/Src/COM.d \
./Core/Src/bmg250.d \
./Core/Src/gfx.d \
./Core/Src/joystick.d \
./Core/Src/lora.d \
./Core/Src/main.d \
./Core/Src/screen.d \
./Core/Src/ssd1351.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F405xx -I"D:/Onedrive/TBZ/TBZ/Projekt Horizon - Dokumente/Projekt/ControllerNew/sw/Core/Inc" -I"D:/Onedrive/TBZ/TBZ/Projekt Horizon - Dokumente/Projekt/ControllerNew/sw/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/Onedrive/TBZ/TBZ/Projekt Horizon - Dokumente/Projekt/ControllerNew/sw/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/Onedrive/TBZ/TBZ/Projekt Horizon - Dokumente/Projekt/ControllerNew/sw/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Onedrive/TBZ/TBZ/Projekt Horizon - Dokumente/Projekt/ControllerNew/sw/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


