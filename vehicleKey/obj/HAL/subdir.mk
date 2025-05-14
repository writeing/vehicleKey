################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEY.c \
../HAL/LED.c \
../HAL/MCU.c \
../HAL/RTC.c \
../HAL/SLEEP.c 

C_DEPS += \
./HAL/KEY.d \
./HAL/LED.d \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 

OBJS += \
./HAL/KEY.o \
./HAL/LED.o \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 



# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/StdPeriphDriver/inc" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/RVMSIS" -I"E:\01.workspace\02.mcu\05.nokey_ch573\vehicleKey\HAL\include" -I"E:\01.workspace\02.mcu\05.nokey_ch573\LIB" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/Profile/include" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/APP/include" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
