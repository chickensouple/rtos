export MAKEFLAGS=--no-print-directory

ROOT_DIR = $(shell pwd)

BUILD_DIR := $(ROOT_DIR)/build
OUTPUT_DIR := $(ROOT_DIR)/bin
PERL_ROOT_DIR := $(subst /,\/,$(ROOT_DIR))
PERL_BUILD_DIR := $(subst /,\/,$(BUILD_DIR))

# dependency files
DEP_FILES := $(shell find $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))) -name '*.d')
-include $(DEP_FILES)

LD_SCRIPT := linker.ld
TIVAWARE_PATH := /home/clark/Documents/TivaWare/
ARM_NONE_EABI_PATH := /opt/gcc-arm-none-eabi-4_7-2014q2/arm-none-eabi/lib

# compiler
CC := arm-none-eabi-gcc
CXX := arm-none-eabi-g++
LD := arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# compiler flags
COMMON_FLAGS := -g -Wall -Wno-unused-parameter \
	-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp \
	-pedantic -DPART_TM4C123GH6PM -ffunction-sections -fdata-sections \
	-DTARGET_IS_BLIZZARD_RA1 -nostdlib -fno-exceptions

CXX_COMMON_FLAGS := $(COMMON_FLAGS) -std=c++11

CC_COMMON_FLAGS := $(COMMON_FLAGS) -std=c99

# library linker flags
LD_COMMON_FLAGS := -T $(ROOT_DIR)/$(LD_SCRIPT) --entry ResetISR --gc-sections \
	-L $(TIVAWARE_PATH)/driverlib/gcc -ldriver -nostdlib \
	-L $(ARM_NONE_EABI_PATH) 

# include flags
INCLUDE_COMMON := -I. -I$(TIVAWARE_PATH)

OBJECT_PATH := $(subst $(ROOT_DIR), $(BUILD_DIR), $(shell pwd))
CXX_OBJECTS := $(addprefix $(OBJECT_PATH)/, $(CXX_SOURCES:.cpp=.cpp.o))
C_OBJECTS := $(addprefix $(OBJECT_PATH)/, $(C_SOURCES:.c=.c.o))
ASM_OBJECTS := $(addprefix $(OBJECT_PATH)/, $(ASM_SOURCES:.s=.s.o))

$(OBJECT_PATH)/%.cpp.o: %.cpp
# mkdir will recreate the file structure of the original
	@mkdir -p $(dir $@)
	@$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $< | \
		perl -pe 's/([a-zA-Z0-9_\/-]*)\.((?!o)[a-zA-Z]*)/$$1.$$2/g' | \
		perl -pe 's/([a-zA-Z0-9_\/-]*)\.o/$(subst /,\/,$(dir $@))$$1.cpp.o/g' > $@.d
	@echo "Object [$@]"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -S -o $(addsuffix .s, $(basename $@)) $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $(addsuffix .s, $(basename $@))

$(OBJECT_PATH)/%.c.o: %.c
# mkdir will recreate the file structure of the original
	@mkdir -p $(dir $@)
	@$(CC) -MM $(CCFLAGS) $(INCLUDES) $< | \
		perl -pe 's/([a-zA-Z0-9_\/-]*)\.((?!o)[a-zA-Z]*)/$$1.$$2/g' | \
		perl -pe 's/([a-zA-Z0-9_\/-]*)\.o/$(subst /,\/,$(dir $@))$$1.c.o/g' > $@.d
	@echo "Object [$@]"
	@$(CC) $(CCFLAGS) $(INCLUDES) -S -o $(addsuffix .s, $(basename $@)) $<
	@$(CC) $(CCFLAGS) $(INCLUDES) -c -o $@ $(addsuffix .s, $(basename $@))

$(OBJECT_PATH)/%.s.o: %.s
# mkdir will recreate the file structure of the original
	@mkdir -p $(dir $@)
	@echo "Object [$@]"
	@$(CC) $(CCFLAGS) $(INCLUDES) -c -o $@ $<
