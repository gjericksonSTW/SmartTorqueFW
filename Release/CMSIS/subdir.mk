################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL43Z4.c 

OBJS += \
./CMSIS/system_MKL43Z4.o 

C_DEPS += \
./CMSIS/system_MKL43Z4.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DCPU_MKL43Z256VLH4_cm0plus -DCPU_MKL43Z256VLH4 -DSDK_DEBUGCONSOLE=1 -D__NEWLIB__ -I"C:\SmartTorque\SmartTorqueFW2\source" -I"C:\SmartTorque\SmartTorqueFW2\hostbgapi" -I"C:\SmartTorque\SmartTorqueFW2" -I"C:\SmartTorque\SmartTorqueFW2\drivers" -I"C:\SmartTorque\SmartTorqueFW2\CMSIS" -I"C:\SmartTorque\SmartTorqueFW2\freertos" -I"C:\SmartTorque\SmartTorqueFW2\utilities" -I"C:\SmartTorque\SmartTorqueFW2\startup" -I"C:\SmartTorque\SmartTorqueFW2\board" -O0 -fno-common -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


