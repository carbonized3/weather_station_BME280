################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := I2C_BH1750+BME280+LCD1602
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
I2C_BH1750+BME280+LCD1602.elf \

MAP_FILES += \
I2C_BH1750+BME280+LCD1602.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
I2C_BH1750+BME280+LCD1602.list \

OBJCOPY_HEX += \
I2C_BH1750+BME280+LCD1602.hex \


# All Target
all: main-build

# Main-build Target
main-build: I2C_BH1750+BME280+LCD1602.elf secondary-outputs

# Tool invocations
I2C_BH1750+BME280+LCD1602.elf I2C_BH1750+BME280+LCD1602.map: $(OBJS) $(USER_OBJS) C:\Users\Rinat\STM32CubeIDE\workspace_1.12.0\I2C_BH1750+BME280+LCD1602\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "I2C_BH1750+BME280+LCD1602.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Rinat\STM32CubeIDE\workspace_1.12.0\I2C_BH1750+BME280+LCD1602\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="I2C_BH1750+BME280+LCD1602.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

I2C_BH1750+BME280+LCD1602.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "I2C_BH1750+BME280+LCD1602.list"
	@echo 'Finished building: $@'
	@echo ' '

I2C_BH1750+BME280+LCD1602.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "I2C_BH1750+BME280+LCD1602.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) I2C_BH1750+BME280+LCD1602.elf I2C_BH1750+BME280+LCD1602.hex I2C_BH1750+BME280+LCD1602.list I2C_BH1750+BME280+LCD1602.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
