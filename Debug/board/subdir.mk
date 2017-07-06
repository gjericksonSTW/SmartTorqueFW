################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/mtb.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/mtb.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/mtb.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DCPU_MKL43Z256VLH4_cm0plus -DCPU_MKL43Z256VLH4 -DSDK_DEBUGCONSOLE=1 -I"C:\SmartTorque\SmartTorqueFW2\source" -I"C:\SmartTorque\SmartTorqueFW2\hostbgapi" -I"C:\SmartTorque\SmartTorqueFW2\board" -I"C:\SmartTorque\SmartTorqueFW2" -I"C:\SmartTorque\SmartTorqueFW2\drivers" -I"C:\SmartTorque\SmartTorqueFW2\CMSIS" -I"C:\SmartTorque\SmartTorqueFW2\freertos" -I"C:\SmartTorque\SmartTorqueFW2\utilities" -I"C:\SmartTorque\SmartTorqueFW2\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


