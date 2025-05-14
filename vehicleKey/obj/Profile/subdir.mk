################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/battservice.c \
../Profile/devinfoservice.c \
../Profile/hidconsumerservice.c \
../Profile/hiddev.c \
../Profile/scanparamservice.c 

C_DEPS += \
./Profile/battservice.d \
./Profile/devinfoservice.d \
./Profile/hidconsumerservice.d \
./Profile/hiddev.d \
./Profile/scanparamservice.d 

OBJS += \
./Profile/battservice.o \
./Profile/devinfoservice.o \
./Profile/hidconsumerservice.o \
./Profile/hiddev.o \
./Profile/scanparamservice.o 



# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/StdPeriphDriver/inc" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/RVMSIS" -I"E:\01.workspace\02.mcu\05.nokey_ch573\vehicleKey\HAL\include" -I"E:\01.workspace\02.mcu\05.nokey_ch573\LIB" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/Profile/include" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/APP/include" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
