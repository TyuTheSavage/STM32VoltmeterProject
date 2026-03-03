################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/RTE/rte.c 

OBJS += \
./Core/RTE/rte.o 

C_DEPS += \
./Core/RTE/rte.d 


# Each subdirectory must supply rules for building sources it contributes
Core/RTE/%.o Core/RTE/%.su Core/RTE/%.cyclo: ../Core/RTE/%.c Core/RTE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/OS -I../Core/HAL -I../Core/LCD -I../Core/RTE -I../Core/System -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-RTE

clean-Core-2f-RTE:
	-$(RM) ./Core/RTE/rte.cyclo ./Core/RTE/rte.d ./Core/RTE/rte.o ./Core/RTE/rte.su

.PHONY: clean-Core-2f-RTE

