# Modified KTH labs makefile

# PIC32 device number
DEVICE		= 32MX320F128H

# UART settings for programmer
TTYDEV		?=/dev/ttyUSB0
TTYBAUD		?=115200

# Name of the project
PROGVER		= 0.1
PROGNAME	= digichess

PROG_FULLNAME = $(PROGNAME)_v$(PROGVER)

BUILD_DIR=build
SRC_DIR=src
INC_DIR=include

# Linkscript
LINKSCRIPT	:= p$(shell echo "$(DEVICE)" | tr '[:upper:]' '[:lower:]').ld

# Compiler and linker flags
CFLAGS		+= -std=c11 -ffreestanding -march=mips32r2 -msoft-float -Wa,-msoft-float
ASFLAGS		+= -msoft-float
LDFLAGS		+= -T $(LINKSCRIPT)

# Filenames
ELFFILE		= $(PROG_FULLNAME).elf
HEXFILE		= $(PROG_FULLNAME).hex

# Find all source files automatically
CFILES      = $(wildcard $(SRC_DIR)/*.c)
ASFILES     = $(wildcard $(SRC_DIR)/*.S)
SYMSFILES	= $(wildcard $(SRC_DIR)/*.syms)

# TODO: Implement a separate /drivers directory for device drivers (e.g. ili9341 and ws2812)

# Object file names
OBJFILES    = $(notdir $(CFILES:.c=.c.o))
OBJFILES    +=$(notdir $(ASFILES:.S=.S.o))
OBJFILES	+=$(notdir $(SYMSFILES:.syms=.syms.o))

OBJFILES_BUILD	=$(patsubst %, $(BUILD_DIR)/%, $(OBJFILES))

# Hidden directory for dependency files
DEPDIR = $(BUILD_DIR)/.deps
df = $(DEPDIR)/$(*F)

.PHONY: all clean install envcheck dev test
.SUFFIXES:

all: build_dir $(HEXFILE)

dev: all install

test:
	@echo "NYI: Tests are on the todo list"

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
%.c.o: $(SRC_DIR)/%.c envcheck | $(DEPDIR)
	$(CC) $(CFLAGS) -c -MD -o $(BUILD_DIR)/$@ $< -I$(INC_DIR)
	@cp $(BUILD_DIR)/$*.c.d $(df).c.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_DIR)/$*.c.d >> $(df).c.P; $(RM) $(BUILD_DIR)/$*.c.d

# Compile ASM files with C pre-processor directives
%.S.o: $(SRC_DIR)/%.S envcheck | $(DEPDIR)
	$(CC) $(CFLAGS) $(ASFLAGS) -c -MD -o $(BUILD_DIR)/$@ $< -I$(INC_DIR)
	@cp $(BUILD_DIR)/$*.S.d $(df).S.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_DIR)/$*.S.d >> $(df).S.P; $(RM) $(BUILD_DIR)/$*.S.d

# Link symbol lists to object files
%.syms.o: $(SRC_DIR)/%.syms
	$(LD) -o $(BUILD_DIR)/$@ -r --just-symbols=$<

build_dir:
	mkdir -p $(BUILD_DIR)

# Check dependencies
-include $(CFILES:%.c=$(DEPDIR)/%.c.P)
-include $(ASFILES:%.S=$(DEPDIR)/%.S.P)
