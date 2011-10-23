#
# Generic Makefile for MSP430-based projects
#
# (c) 2011, NoccyLabs.info
#
# This script makes use of mspdebug to identify and program the device. If it
# is located in a location outside of the path, change the following line to
# point to the proper location. Also, the driver is defined here:
MSPDEBUG = mspdebug
MSPTYPE  = rf2500
#
# The MCU to use can either be defined on the command line:
#   export MCU=msp430g2253
# Or explicitly defined in the makefile:
#   MCU=msp430g2553
# Or the preferred way, have it reported by mspdebug:
MCU?=$(shell $(MSPDEBUG) -q $(MSPTYPE) "exit" 2>/dev/null | grep -i "Device:" | cut -c 9- | tr "[A-Z]" "[a-z]")
#
# Source files and target binary, define your source files here to have them
# compiled, and define the target basename. An .elf binary will be created as
# well as a .hex file:
SOURCES  = main.c suart.c i2c.c rtc.c
SOURCESA =
TARGET   = rtcctl
INCLUDES =
LIBS     =

# Compiler and other binaries. No need to change these really, unless you know
# what you are doing.
CC       = msp430-gcc
OBJCOPY  = msp430-objcopy
SIZE     = msp430-size -t
# Flags and command lines
CFLAGS   = -mmcu=$(MCU) -g -Os -Wall -Wunused $(INCLUDES)
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) -Wl,-Map=$(TARGET).map
# Object files and listings
OBJS     = $(SOURCES:.c=.o) $(SOURCESA:.asm=.o)
LSTS     = $(SOURCES:.c=.lst)

# Phony targets; all and clean
.phony: all bin clean listing prog identify

# All, to build the binary and program it
all: bin prog

# Binary, depends on the object files
bin: $(TARGET).elf $(TARGET).hex
$(TARGET).elf: $(OBJS)
ifndef $(MCU)
	@echo "ERROR: MCU not defined or programmer not connected."
	@exit 1
endif
	$(CC) $(LDFLAGS) -o $(TARGET).elf $(OBJS) $(LIBS)
	$(SIZE) $(TARGET).elf

listing: $(LSTS)

# Compile the object files
%.o: %.c
ifndef $(MCU)
	@echo "ERROR: MCU not defined or programmer not connected."
	@exit 1
endif
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.asm
ifndef $(MCU)
	@echo "ERROR: MCU not defined or programmer not connected."
	@exit 1
endif
	$(CC) -c $(ASFLAGS) -o $@ $<

# Create hex files
%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

# rule for making assembler source listing, to see the code
%.lst: %.c
	$(CC) -c $(CFLAGS) -Wa,-anlhd $< > $@

# Clean
clean:
	rm -fr $(TARGET).hex $(TARGET).elf $(TARGET).map $(OBJS) $(LSTS)

prog: $(TARGET).elf
	$(MSPDEBUG) $(MSPTYPE) "prog $(TARGET).elf"

sim: $(TARGET).elf
	@echo "Type 'prog $(TARGET).elf' to load the program in the simulator"
	$(MSPDEBUG) sim 

identify:
	@echo "Device: $(MCU)"

help:
	@echo "Target binary:"
	@echo "  $(TARGET)"
	@echo
	@echo "Source files:"
	@echo "  $(SOURCES) $(SOURCESASM)"
	@echo 
	@echo "Supported rules:"
	@echo "  all       Build and program the device"
	@echo "  bin       Only build binary"
	@echo "  prog      Only program device with binary"
	@echo "  sim       Open the binary in the mspdebug simulator"
	@echo "  clean     Clean the build environment"
	@echo "  listing   Assembly source listings"
	@echo "  identify  Identify the attached MCU"


