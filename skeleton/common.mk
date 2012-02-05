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
SIZE     = msp430-size -x
STRIP    = msp430-strip
# Flags and command lines
#  if your main never returns: -mendup-at=main  (saves 6 bytes of ram)
CFLAGS   = -mmcu=$(MCU) -ffunction-sections -fdata-sections -fno-inline-small-functions \
	-g -O2 -Wall -Wunused $(INCLUDES) $(CXXFLAGS)
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) -Wl,-Map=$(TARGET).map
# Object files and listings
OBJS     = $(SOURCEC:.c=.c.o) $(SOURCEASM:.asm=.asm.o) $(SOURCECPP:.cpp=.cpp.o)
LSTS     = $(SOURCEC:.c=.lst) $(SOURCECPP:.cpp=.lst)
ASMTYPE ?= gcc
AR      ?= msp430-ar
ARLFAGS ?= r

# Phony targets; all and clean
.phony: all bin lib clean listing prog identify package help

# Target rules
all: $(BUILD)
lib: $(TARGET).a
bin: $(TARGET).elf $(TARGET).hex

# Build library
$(TARGET).a: $(OBJS)
	printf "[AR ] %s.a: %s\n" "$(TARGET)" "$(OBJS)"
	ar r -o $(TARGET).a $(OBJS)

# Build binary
$(TARGET).elf: $(OBJS)
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	exit 1
endif
	printf "[LD ] %s.elf: %s\n" "$(TARGET)" "$(OBJS)"
	$(CC) $(LDFLAGS) $(LIBPATH) -o $(TARGET).elf $(OBJS) $(LIBS) 
	$(SIZE) $(TARGET).elf

listing: $(LSTS)

# Compile the object files
%.c.o: %.c
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	echo $(MCU)
	exit 1
endif
	printf "[CC ] %s\n" "$@"
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

# Compile the object files
%.cpp.o: %.cpp
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	echo $(MCU)
	exit 1
endif
	printf "[CPP] %s\n" "$@"
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

%.asm.o: %.asm
ifeq ($(MCU),)
	echo "ERROR: MCU not defined or programmer not connected."
	exit 1
endif
ifeq ($(ASMTYPE),gcc)
	printf "[ASM] %s (%s)\n" "$@" "gcc"
	$(CC) -D_GNU_ASSEMBLER_ -c $(ASFLAGS) -o $@ $<
endif
ifeq ($(ASMTYPE),naken)
	printf "[ASM] %s (%s)\n" "$@" "naken"
	$(NAKENASM) -e -o $@ $<
endif

# Create hex files
%.hex: %.elf
	printf "[OBJ] %s\n" "$@"
	$(OBJCOPY) -O ihex $< $@

# rule for making assembler source listing, to see the code
%.lst: %.c
	printf "[LST] %s\n" "$@"
	$(CC) -c $(CFLAGS) -Wa,-anlhd $< > $@

# Clean
clean:
ifeq ($(BUILD),lib)
	rm -fr $(TARGET).a $(OBJS)
else
	rm -fr $(TARGET).hex $(TARGET).elf $(TARGET).map $(OBJS) $(LSTS)
endif

# Docs
docs: Doxyfile
	printf "[DOC] Doxygen\n"
	doxygen

prog: $(TARGET).elf
	echo "[:::] programming device: $(MCU)"
	$(MSPDEBUG) -q $(MSPTYPE) "prog $(TARGET).elf"

sim: $(TARGET).elf
	echo "Type 'prog $(TARGET).elf' to load the program in the simulator"
	$(MSPDEBUG) sim 

identify:
	@echo "Device: $(MCU)"

package: clean
	@echo "Packaging source..."
	@bash -c "test -e $(TARGET)-src.tgz && rm -rf $(TARGET)-src.tgz; exit 0"
	@echo "Copying files..."
	@mkdir /tmp/$(TARGET)-src
	@cp * /tmp/$(TARGET)-src
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
