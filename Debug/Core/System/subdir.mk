################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/System/stm32f0xx_it.c \
../Core/System/syscalls.c \
../Core/System/sysmem.c \
../Core/System/system_stm32f0xx.c 

OBJS += \
./Core/System/stm32f0xx_it.o \
./Core/System/syscalls.o \
./Core/System/sysmem.o \
./Core/System/system_stm32f0xx.o 

C_DEPS += \
./Core/System/stm32f0xx_it.d \
./Core/System/syscalls.d \
./Core/System/sysmem.d \
./Core/System/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/System/%.o Core/System/%.su Core/System/%.cyclo: ../Core/System/%.c Core/System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/OS -I../Core/HAL -I../Core/LCD -I../Core/RTE -I../Core/System -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-System

clean-Core-2f-System:
	-$(RM) ./Core/System/stm32f0xx_it.cyclo ./Core/System/stm32f0xx_it.d ./Core/System/stm32f0xx_it.o ./Core/System/stm32f0xx_it.su ./Core/System/syscalls.cyclo ./Core/System/syscalls.d ./Core/System/syscalls.o ./Core/System/syscalls.su ./Core/System/sysmem.cyclo ./Core/System/sysmem.d ./Core/System/sysmem.o ./Core/System/sysmem.su ./Core/System/system_stm32f0xx.cyclo ./Core/System/system_stm32f0xx.d ./Core/System/system_stm32f0xx.o ./Core/System/system_stm32f0xx.su

.PHONY: clean-Core-2f-System

