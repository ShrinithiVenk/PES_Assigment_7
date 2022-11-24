################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/Autotune.c \
../source/DAC.c \
../source/DMA.c \
../source/TPM.c \
../source/autocorrelate.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sin.c \
../source/systick.c \
../source/test_sine.c 

C_DEPS += \
./source/ADC.d \
./source/Autotune.d \
./source/DAC.d \
./source/DMA.d \
./source/TPM.d \
./source/autocorrelate.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sin.d \
./source/systick.d \
./source/test_sine.d 

OBJS += \
./source/ADC.o \
./source/Autotune.o \
./source/DAC.o \
./source/DMA.o \
./source/TPM.o \
./source/autocorrelate.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sin.o \
./source/systick.o \
./source/test_sine.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune\board" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune\source" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune\drivers" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune\CMSIS" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune\utilities" -I"C:\Users\itssh\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PBKDF2\Autotune\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ADC.d ./source/ADC.o ./source/Autotune.d ./source/Autotune.o ./source/DAC.d ./source/DAC.o ./source/DMA.d ./source/DMA.o ./source/TPM.d ./source/TPM.o ./source/autocorrelate.d ./source/autocorrelate.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sin.d ./source/sin.o ./source/systick.d ./source/systick.o ./source/test_sine.d ./source/test_sine.o

.PHONY: clean-source

