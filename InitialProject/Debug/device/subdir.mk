################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MK22F51212.c 

OBJS += \
./device/system_MK22F51212.o 

C_DEPS += \
./device/system_MK22F51212.d 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VDC12 -DCPU_MK22FN512VDC12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\board" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\source" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\drivers" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\component\serial_manager" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\utilities" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\component\uart" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\component\lists" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\CMSIS" -I"C:\Users\Dave\Documents\MCUXpressoIDE_11.5.0_7232\workspace\InitialProject\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

