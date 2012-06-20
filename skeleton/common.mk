#
# Generic Makefile for MSP430-based projects
#
# (c) 2011, NoccyLabs.info
#
# DO NOT MODIFY THIS SCRIPT. INSTEAD INCLUDE IT IN YOUR OWN MAKEFILE LIKE THIS:
#
#   SOURCES  = foo.c
#   TARGET   = bar
#   include common.mk
#
# You can define more variables, such as SOURCESA for assembly source files,
# INCLUDES to point to include dirs (such as -Ilib/include), LIBS to point to
# a location where to find libraries (such as -Llib).
#
#
#
# This script makes use of mspdebug to identify and program the device. If it
# is located in a location outside of the path, change the following line to
# point to the proper location. Also, the driver is defined here:
MSPDEBUG?= mspdebug
MSPTYPE ?= rf2500
BUILD   ?= bin prog docs
SOURCEC ?= $(SOURCES)

# The MCU to use can either be defined on the command line:
#   export MCU=msp430g2253
# Or explicitly defined in the makefile:
#   MCU=msp430g2553
# Or the preferred way, have it reported by mspdebug:
#export MCU ?= $(shell $(MSPDEBUG) -q $(MSPTYPE) "exit" 2>/dev/null | grep -i "Device:" | cut -c 9- | tr "[A-Z]" "[a-z]")
export MCU ?= $(shell msp430-identify)

# Compiler and other binaries. No need to change these really, unless you know
# what you are doing.
CC       = msp430-gcc
NAKENASM = naken430asm
GCCASM   = msp430-gcc
OBJCOPY  = msp430-objcopy
SIZE     = msp430-size -Axd 
STRIP    = msp430-strip
# Flags and command lines
#  if your main never returns: -mendup-at=main  (saves 6 bytes of ram)
CFLAGS   = -mmcu=$(MCU) -ffunction-sections -fdata-sections -fno-inline-small-functions \
	-g -Os -Wall -Wunused $(INCLUDES) $(CXXFLAGS)
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) -Wl,-Map=$(TARGET).map
# Object files and listings
OBJS     = $(strip $(SOURCEC:.c=.c.o) $(SOURCEASM:.asm=.asm.o) $(SOURCEASM:.s43=.s43.o) $(SOURCECPP:.cpp=.cpp.o) $(SOURCECPP:.cc=.cc.o))
LSTS     = $(strip $(SOURCEC:.c=.c.lst) $(SOURCECPP:.cpp=.cpp.lst) $(SOURCECPP:.cc=.cc.lst))
ASMTYPE ?= gcc
AR      ?= msp430-ar
ARLFAGS ?= r

HDR_ASM  = [\033[0;32m%-3s\033[0m]
HDR_CC   = [\033[0;32m%-3s\033[0m]
HDR_AR   = [\033[0;33m%-3s\033[0m]
HDR_LD   = [\033[0;36m%-3s\033[0m]
HDR_HEX  = [\033[0;36m%-3s\033[0m]
HDR_LST  = [\033[0;35m%-3s\033[0m]
HDR_RM   = [\033[0;33m%-3s\033[0m]

# Phony targets; all and clean
.phony: all bin lib clean listing prog identify package help

# Target rules
all: $(BUILD)
lib: $(TARGET).a
bin: $(TARGET).elf $(TARGET).hex

# Build library
$(TARGET).a: $(OBJS)
	printf "$(HDR_AR) \033[1m%s.a\033[0m: \033[37m%s\033[0m\n" "AR" "$(TARGET)" "$(strip $(OBJS))"
	ar r -o $(TARGET).a $(OBJS) 2>/dev/null

# Build binary
$(TARGET).elf: $(OBJS)
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	exit 1
endif
	printf "$(HDR_LD) \033[1m%s.elf\033[0m: \033[37m%s\033[0m %s\n" "LD" "$(TARGET)" "$(strip $(OBJS))" "$(if $(LIBS),(+$(subst -l,,$(LIBS))),)"
	$(CC) $(LDFLAGS) $(LIBPATH) -o $(TARGET).elf $(OBJS) $(LIBS) 

size: $(TARGET)
	$(SIZE) $(TARGET).elf | grep " " | grep -v "$(TARGET)"

listing: $(LSTS)
	
# Compile the object files
%.c.o: %.c
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	echo $(MCU)
	exit 1
endif
	printf "$(HDR_CC) %s\n" "CC" "$@"
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

# Compile the object files
%.cpp.o: %.cpp
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	echo $(MCU)
	exit 1
endif
	printf "$(HDR_CC) %s\n" "CPP" "$@"
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

%.asm.o: %.asm
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	exit 1
endif
	printf "$(HDR_ASM) %s (%s)\n" "ASM" "$@" "naken"
	$(NAKENASM) -e -o $@ $<

%.s43.o: %.s43
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	exit 1
endif
	printf "$(HDR_ASM) %s (%s)\n" "S43" "$@" "gcc"
	$(CC) -D_GNU_ASSEMBLER_ -c $(ASFLAGS) -o $@ $<

# Create hex files
%.hex: %.elf
	printf "$(HDR_HEX) %s: %s\n" "HEX" "$@" "$<"
	$(OBJCOPY) -O ihex $< $@

# rule for making assembler source listing, to see the code
%.c.lst: %.c
	printf "$(HDR_LST) %s\n" "LST" "$@"
	$(CC) -c $(CFLAGS) -Wa,-anlhd $< > $@

# Clean
clean:
ifeq ($(BUILD),lib)
	printf "$(HDR_RM) $(TARGET).a $(OBJS)\n" "RM "
	rm -fr $(TARGET).a $(OBJS)
else
	printf "$(HDR_RM) $(TARGET).elf $(TARGET).hex $(TARGET).map $(OBJS) $(LSTS)\n" "RM "
	rm -fr $(TARGET).hex $(TARGET).elf $(TARGET).map $(OBJS) $(LSTS)
endif

# Docs
docs: Doxyfile
	printf "[\033[38;5;148m%-3s\033[39m] Doxygen\n" "DOC"
	doxygen 2>doxygen.err >doxygen.log

interactive: prog
	printf "[\033[38;5;148m%-3s\033[39m] entering interactive mode\n" "MSP"
	$(MSPDEBUG) -q $(MSPTYPE)

 strip: 
	printf "[\033[38;5;148m%-3s\033[39m] Stripping debug information...\n" "---"
	$(STRIP) $(TARGET).elf

prog: $(TARGET).elf
	printf "[\033[38;5;148m%-3s\033[39m] programming device: \033[1m%s\033[0m\n" "MSP" "$(MCU)"
	$(MSPDEBUG) -q $(MSPTYPE) "prog $(TARGET).elf" >/dev/null 2>/dev/null

sim: $(TARGET).elf
	echo "Type 'prog $(TARGET).elf' to load the program in the simulator"
	$(MSPDEBUG) sim 

identify:
	@echo "Device: $(MCU)"

package: clean
	@echo "Packaging source..."
	@bash -c "test -e $(TARGET)-src.tgz && rm -rf $(TARGET)-src.tgz; exit 0"
	@echo "Copying files..."
	@mkdir -p /tmp/$(TARGET)-src
	@cp -R * /tmp/$(TARGET)-src
	@echo "Creating tarball..."
	@cd /tmp && tar cfz $(TARGET)-src.tgz $(TARGET)-src
	@mv /tmp/$(TARGET)-src.tgz .
	@echo "Cleaning up..."
	@rm -rf /tmp/$(TARGET)-src

help:
	@echo "Build type:"
	@echo "  $(BUILD)"
	@echo "Target binary:"
	@echo "  $(TARGET)"
	@echo "Source files:"
	@echo "  $(SOURCES) $(SOURCESASM)"
	@echo "MCU:"
	@echo "  $(MCU)"
	@echo 
	@echo "Supported rules:"
	@echo "  all       Same as $(BUILD)"
	@echo "  bin       Only build binary (if supported)"
	@echo "  lib       Only build library (if supported)"
	@echo "  listing   Make assembly .lst files from the source"
	@echo "  prog      Only program device with binary"
	@echo "  sim       Open the binary in the mspdebug simulator"
	@echo "  clean     Clean the build environment"
	@echo "  listing   Assembly source listings"
	@echo "  identify  Identify the attached MCU"
	@echo "  package   Create tarball package"

.SILENT: 
