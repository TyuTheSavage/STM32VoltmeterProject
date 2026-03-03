################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LCD/font.c \
../Core/LCD/lcd_st7565.c 

OBJS += \
./Core/LCD/font.o \
./Core/LCD/lcd_st7565.o 

C_DEPS += \
./Core/LCD/font.d \
./Core/LCD/lcd_st7565.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LCD/%.o Core/LCD/%.su Core/LCD/%.cyclo: ../Core/LCD/%.c Core/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Core/OS -I../Core/HAL -I../Core/LCD -I../Core/RTE -I../Core/System -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-LCD

clean-Core-2f-LCD:
	-$(RM) ./Core/LCD/font.cyclo ./Core/LCD/font.d ./Core/LCD/font.o ./Core/LCD/font.su ./Core/LCD/lcd_st7565.cyclo ./Core/LCD/lcd_st7565.d ./Core/LCD/lcd_st7565.o ./Core/LCD/lcd_st7565.su

.PHONY: clean-Core-2f-LCD

