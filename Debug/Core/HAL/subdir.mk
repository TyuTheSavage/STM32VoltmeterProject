################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/HAL/stm32f0xx_hal_msp.c \
../Core/HAL/stm32f0xx_hal_timebase_tim.c 

OBJS += \
./Core/HAL/stm32f0xx_hal_msp.o \
./Core/HAL/stm32f0xx_hal_timebase_tim.o 

C_DEPS += \
./Core/HAL/stm32f0xx_hal_msp.d \
./Core/HAL/stm32f0xx_hal_timebase_tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/HAL/%.o Core/HAL/%.su Core/HAL/%.cyclo: ../Core/HAL/%.c Core/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/OS -I../Core/HAL -I../Core/LCD -I../Core/RTE -I../Core/System -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-HAL

clean-Core-2f-HAL:
	-$(RM) ./Core/HAL/stm32f0xx_hal_msp.cyclo ./Core/HAL/stm32f0xx_hal_msp.d ./Core/HAL/stm32f0xx_hal_msp.o ./Core/HAL/stm32f0xx_hal_msp.su ./Core/HAL/stm32f0xx_hal_timebase_tim.cyclo ./Core/HAL/stm32f0xx_hal_timebase_tim.d ./Core/HAL/stm32f0xx_hal_timebase_tim.o ./Core/HAL/stm32f0xx_hal_timebase_tim.su

.PHONY: clean-Core-2f-HAL

