CXX_SOURCES := src/main.cpp
C_SOURCES := src/startup.c
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

$(FIRMWARE): $(CXX_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS)
	@$(LD) $(CXX_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS) $(LDFLAGS) -o $(FIRMWARE).tmp
	@$(OBJCOPY) -O binary $(FIRMWARE).tmp $@.bin
	@rm $(FIRMWARE).tmp

clean: 
	@rm -f -r $(BUILD_DIR)
	@rm -f -r $(OUTPUT_DIR)

cleandep:
	@find . -name "*.d" -type f -delete

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OUTPUT_DIR)

upload: all
	$(LM4FLASH) $(FIRMWARE).bin
	@echo "Finished Upload"

.PHONY: all program clean cleandep directories upload

