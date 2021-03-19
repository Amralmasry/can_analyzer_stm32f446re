################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Services_layers/CAN_Queue.c \
../src/Services_layers/GeneralTimer.c \
../src/Services_layers/Queue.c \
../src/Services_layers/String_Queue.c \
../src/Services_layers/delay.c \
../src/Services_layers/utility.c 

OBJS += \
./src/Services_layers/CAN_Queue.o \
./src/Services_layers/GeneralTimer.o \
./src/Services_layers/Queue.o \
./src/Services_layers/String_Queue.o \
./src/Services_layers/delay.o \
./src/Services_layers/utility.o 

C_DEPS += \
./src/Services_layers/CAN_Queue.d \
./src/Services_layers/GeneralTimer.d \
./src/Services_layers/Queue.d \
./src/Services_layers/String_Queue.d \
./src/Services_layers/delay.d \
./src/Services_layers/utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/Services_layers/%.o: ../src/Services_layers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"E:/New folder/can_analyzer_stm32f446re/StdPeriph_Driver/inc" -I"E:/New folder/can_analyzer_stm32f446re/src/MCAL" -I"E:/New folder/can_analyzer_stm32f446re/Config" -I"E:/New folder/can_analyzer_stm32f446re/inc" -I"E:/New folder/can_analyzer_stm32f446re/CMSIS/device" -I"E:/New folder/can_analyzer_stm32f446re/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


