################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/SmartTorqueFW.c \
../source/_ADCSense.c \
../source/_Bluetooth.c \
../source/_Display.c \
../source/_FRAM.c \
../source/_HMI.c \
../source/_RTC.c \
../source/_Sys_Control.c \
../source/_Timer.c 

OBJS += \
./source/SmartTorqueFW.o \
./source/_ADCSense.o \
./source/_Bluetooth.o \
./source/_Display.o \
./source/_FRAM.o \
./source/_HMI.o \
./source/_RTC.o \
./source/_Sys_Control.o \
./source/_Timer.o 

C_DEPS += \
./source/SmartTorqueFW.d \
./source/_ADCSense.d \
./source/_Bluetooth.d \
./source/_Display.d \
./source/_FRAM.d \
./source/_HMI.d \
./source/_RTC.d \
./source/_Sys_Control.d \
./source/_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DCPU_MKL43Z256VLH4_cm0plus -DCPU_MKL43Z256VLH4 -DSDK_DEBUGCONSOLE=0 -I"C:\SmartTorque\SmartTorqueFW2\source" -I"C:\SmartTorque\SmartTorqueFW2\hostbgapi" -I"C:\SmartTorque\SmartTorqueFW2\board" -I"C:\SmartTorque\SmartTorqueFW2" -I"C:\SmartTorque\SmartTorqueFW2\drivers" -I"C:\SmartTorque\SmartTorqueFW2\CMSIS" -I"C:\SmartTorque\SmartTorqueFW2\freertos" -I"C:\SmartTorque\SmartTorqueFW2\utilities" -I"C:\SmartTorque\SmartTorqueFW2\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


