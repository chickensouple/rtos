CXX_SOURCES := src/main.cpp src/MemoryManagement.cpp src/Scheduler.cpp src/Utility.cpp
C_SOURCES := src/startup.c src/hal/Timer.c src/uartstdio.c
ASM_SOURCES :=

LM4FLASH = /home/clark/Documents/lm4tools/lm4flash/lm4flash

all: program

include common.mk

CXXFLAGS := $(CXX_COMMON_FLAGS)
CCFLAGS := $(CC_COMMON_FLAGS)
INCLUDES := $(INCLUDE_COMMON)
LDFLAGS := $(LD_COMMON_FLAGS) 

FIRMWARE := $(OUTPUT_DIR)/firmware

program: directories $(FIRMWARE)
	@echo "Built Firmware"
	@arm-none-eabi-size $(CXX_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS) -d

$(FIRMWARE): $(CXX_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS)
	@$(LD) $(CXX_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS) $(LDFLAGS) -o $(FIRMWARE).obj
	@$(OBJCOPY) -O binary $(FIRMWARE).obj $@.out

clean: 
	@rm -f -r $(BUILD_DIR)
	@rm -f -r $(OUTPUT_DIR)

cleandep:
	@find . -name "*.d" -type f -delete

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OUTPUT_DIR)

upload: all
	$(LM4FLASH) $(FIRMWARE).out
	@echo "Finished Upload"

.PHONY: all program clean cleandep directories upload

