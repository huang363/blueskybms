################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LTC6804.c \
../Src/LTC_SPI.c \
../Src/main.c \
../Src/serial.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_hal_timebase_TIM.c \
../Src/stm32l4xx_it.c \
../Src/system_stm32l4xx.c 

OBJS += \
./Src/LTC6804.o \
./Src/LTC_SPI.o \
./Src/main.o \
./Src/serial.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_hal_timebase_TIM.o \
./Src/stm32l4xx_it.o \
./Src/system_stm32l4xx.o 

C_DEPS += \
./Src/LTC6804.d \
./Src/LTC_SPI.d \
./Src/main.d \
./Src/serial.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_hal_timebase_TIM.d \
./Src/stm32l4xx_it.d \
./Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak='__attribute__((weak))' -D__packed='__attribute__((__packed__))' -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -I"/Users/elenahuang/Documents/bluesky_bms/sandbox_LTC/Inc" -I"/Users/elenahuang/Documents/bluesky_bms/sandbox_LTC/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/elenahuang/Documents/bluesky_bms/sandbox_LTC/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/elenahuang/Documents/bluesky_bms/sandbox_LTC/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/elenahuang/Documents/bluesky_bms/sandbox_LTC/Drivers/CMSIS/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


