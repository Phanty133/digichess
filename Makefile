# Modified KTH labs makefile
# a bit of a mess but ¯\_(ツ)_/¯

# PIC32 device number
DEVICE		= 32MX340F512H

# UART settings for programmer
TTYDEV		?=/dev/ttyUSB0
TTYBAUD		?=115200

# Name of the project
PROGVER		= 1
PROGNAME	= digichess

PROG_FULLNAME = $(PROGNAME)_v$(PROGVER)

BUILD_DIR=build
SRC_DIR=src
INC_DIRS=include

# Linkscript
LINKSCRIPT	:= p$(shell echo "$(DEVICE)" | tr '[:upper:]' '[:lower:]').ld

# Compiler and linker flags
CFLAGS		+= -std=c11 -ffreestanding -march=mips32r2 -msoft-float -Wa,-msoft-float $(if $(DEFINES),-D $(DEFINES),)

ASFLAGS		+= -msoft-float
LDFLAGS		+= -T $(LINKSCRIPT)

INC_FLAGS	=$(patsubst %, -I%, $(INC_DIRS))

# Filenames
ELFFILE		= $(PROG_FULLNAME).elf
HEXFILE		= $(PROG_FULLNAME).hex

# Find all source files automatically
# Define a recursive wildcard function for traversing the src directory
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CFILES_DIR	= $(call rwildcard,$(SRC_DIR),*.c)
ASFILES_DIR	= $(call rwildcard,$(SRC_DIR),*.S)
SYMSFILES_DIR	= $(call rwildcard,$(SRC_DIR),*.syms)

CFILES		= $(notdir $(CFILES_DIR))
ASFILES     = $(notdir $(ASFILES_DIR))
SYMSFILES	= $(notdir $(SYMSFILES_DIR))

C_DIRS		= $(sort $(dir $(CFILES_DIR)))
AS_DIRS		= $(sort $(dir $(ASFILES_DIR)))
SYMS_DIRS	= $(sort $(dir $(SYMSFILES_DIR)))

SRC_DIRS_DUPL	= $(C_DIRS)
SRC_DIRS_DUPL	+= $(AS_DIRS)
SRC_DIRS_DUPL	+= $(SYMS_DIRS)
SRC_DIRS	= $(sort $(SRC_DIRS_DUPL))

# Object file names

OBJFILES    = $(CFILES:.c=.c.o)
OBJFILES    +=$(ASFILES:.S=.S.o)
OBJFILES	+=$(SYMSFILES:.syms=.syms.o)

OBJFILES_BUILD	=$(patsubst %, $(BUILD_DIR)/%, $(OBJFILES))

# Hidden directory for dependency files
DEPDIR = $(BUILD_DIR)/.deps
df = $(DEPDIR)/$(*F)

.PHONY: all clean install envcheck dev test
.SUFFIXES:

all: build_dir $(HEXFILE)

dev: all install

test:
	@cmake -B $(BUILD_DIR)/cmake
	@cd $(BUILD_DIR)/cmake; make
	@$(BUILD_DIR)/cmake/digichess-tests

clean:
	$(RM) -R $(BUILD_DIR)

envcheck:
	@echo "$(TARGET)" | grep mcb32 > /dev/null || (\
		echo ""; \
		echo " **************************************************************"; \
		echo " * Make sure you have sourced the cross compiling environment *"; \
		echo " * Do this by issuing:                                        *"; \
		echo " * . /path/to/crosscompiler/environment                       *"; \
		echo " **************************************************************"; \
		echo ""; \
		exit 1)

install: envcheck
	$(TARGET)avrdude -v -p $(shell echo "$(DEVICE)" | tr '[:lower:]' '[:upper:]') -c stk500v2 -P "$(TTYDEV)" -b $(TTYBAUD) -U "flash:w:$(BUILD_DIR)/$(HEXFILE)"

$(ELFFILE): $(OBJFILES) envcheck
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $(OBJFILES_BUILD) $(LDFLAGS)

$(HEXFILE): $(ELFFILE) envcheck
	$(TARGET)bin2hex -a $(BUILD_DIR)/$(ELFFILE)

$(DEPDIR):
	@mkdir -p $@

# Compile C files

# The second expansion and foreach stuff is needed to compile the files in all subdirectories
.SECONDEXPANSION:
%.c.o: $$(foreach dir,$(SRC_DIRS),$$(wildcard $$(dir)/$$*.c)) envcheck | $(DEPDIR)
	$(CC) $(CFLAGS) -c -MD -o $(BUILD_DIR)/$@ $< $(INC_FLAGS)
	@cp $(BUILD_DIR)/$*.c.d $(df).c.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_DIR)/$*.c.d >> $(df).c.P; $(RM) $(BUILD_DIR)/$*.c.d

# Compile ASM files with C pre-processor directives
.SECONDEXPANSION:
%.S.o: $$(foreach dir,$(SRC_DIRS),$$(wildcard $$(dir)/$$*.S)) envcheck | $(DEPDIR)
	$(CC) $(CFLAGS) $(ASFLAGS) -c -MD -o $(BUILD_DIR)/$@ $< $(INC_FLAGS)
	@cp $(BUILD_DIR)/$*.S.d $(df).S.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_DIR)/$*.S.d >> $(df).S.P; $(RM) $(BUILD_DIR)/$*.S.d

# Link symbol lists to object files
.SECONDEXPANSION:
%.syms.o: $$(foreach dir,$(SRC_DIRS),$$(wildcard $$(dir)/$$*.syms))
	$(LD) -o $(BUILD_DIR)/$@ -r --just-symbols=$<

build_dir:
	mkdir -p $(BUILD_DIR)

# Check dependencies
-include $(CFILES:%.c=$(DEPDIR)/%.c.P)
-include $(ASFILES:%.S=$(DEPDIR)/%.S.P)
