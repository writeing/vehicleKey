################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RVMSIS/core_riscv.c 

C_DEPS += \
./RVMSIS/core_riscv.d 

OBJS += \
./RVMSIS/core_riscv.o 



# Each subdirectory must supply rules for building sources it contributes
RVMSIS/%.o: ../RVMSIS/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/StdPeriphDriver/inc" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/RVMSIS" -I"E:\01.workspace\02.mcu\05.nokey_ch573\vehicleKey\HAL\include" -I"E:\01.workspace\02.mcu\05.nokey_ch573\LIB" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/Profile/include" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/APP/include" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/thrLib" -I"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/thrLib/FlexibleButton-latest" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
