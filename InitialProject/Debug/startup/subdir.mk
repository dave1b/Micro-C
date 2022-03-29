################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mk22f51212.c 

OBJS += \
./startup/startup_mk22f51212.o 

C_DEPS += \
./startup/startup_mk22f51212.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VDC12 -DCPU_MK22FN512VDC12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\board" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\source" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\drivers" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\component\serial_manager" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\utilities" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\component\uart" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\component\lists" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\CMSIS" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\Micro-C\InitialProject\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


