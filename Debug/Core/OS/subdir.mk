################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/OS/adcTask.c \
../Core/OS/customOS.c \
../Core/OS/displayTask.c 

OBJS += \
./Core/OS/adcTask.o \
./Core/OS/customOS.o \
./Core/OS/displayTask.o 

C_DEPS += \
./Core/OS/adcTask.d \
./Core/OS/customOS.d \
./Core/OS/displayTask.d 


# Each subdirectory must supply rules for building sources it contributes
Core/OS/%.o Core/OS/%.su Core/OS/%.cyclo: ../Core/OS/%.c Core/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/OS -I../Core/HAL -I../Core/LCD -I../Core/RTE -I../Core/System -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-OS

clean-Core-2f-OS:
	-$(RM) ./Core/OS/adcTask.cyclo ./Core/OS/adcTask.d ./Core/OS/adcTask.o ./Core/OS/adcTask.su ./Core/OS/customOS.cyclo ./Core/OS/customOS.d ./Core/OS/customOS.o ./Core/OS/customOS.su ./Core/OS/displayTask.cyclo ./Core/OS/displayTask.d ./Core/OS/displayTask.o ./Core/OS/displayTask.su

.PHONY: clean-Core-2f-OS

