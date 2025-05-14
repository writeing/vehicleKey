################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include Profile/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
vehicleKey.hex \

SECONDARY_LIST += \
vehicleKey.lst \

SECONDARY_SIZE += \
vehicleKey.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: vehicleKey.elf secondary-outputs

# Tool invocations
vehicleKey.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -T "e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -L"e:/01.workspace/02.mcu/05.nokey_ch573/vehicleKey/StdPeriphDriver" -L"E:\01.workspace\02.mcu\05.nokey_ch573\LIB" -L"E:\01.workspace\02.mcu\05.nokey_ch573\vehicleKey\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"vehicleKey.map" --specs=nano.specs --specs=nosys.specs -o "vehicleKey.elf" $(OBJS) $(USER_OBJS) $(LIBS)
vehicleKey.hex: vehicleKey.elf
	@	riscv-none-embed-objcopy -O ihex "vehicleKey.elf" "vehicleKey.hex"
vehicleKey.lst: vehicleKey.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "vehicleKey.elf" > "vehicleKey.lst"
vehicleKey.siz: vehicleKey.elf
	riscv-none-embed-size --format=berkeley "vehicleKey.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) vehicleKey.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets