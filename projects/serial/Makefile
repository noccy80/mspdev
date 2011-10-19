#
# Generic Makefile for MSP430-based projects
#
# (c) 2011, NoccyLabs.info
#
# This script makes use of mspdebug to identify and program the device. If it
# is located in a location outside of the path, change the following line to
# point to the proper location. Also, the driver is defined here:
MSPDEBUG=mspdebug
MSPTYPE=rf2500
#
# The MCU to use can either be defined on the command line:
#   export MCU=msp430g2253
# Or explicitly defined in the makefile:
#   MCU=msp430g2553
# Or the preferred way, have it reported by mspdebug:
MCU?=$(shell $(MSPDEBUG) -q $(MSPTYPE) "exit" 2>/dev/null | grep -i "Device:" | cut -c 9- | tr "[A-Z]" "[a-z]")

# Compiler, compiler flags, linker, linker flags
CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=$(MCU)
CL=msp430-gcc
LFLAGS=

# Object files and target binary
OBJS=main.o suart.o
BIN=main.elf

# Phony targets; all and clean
.phony: all bin clean prog identify

# All, to build the binary and program it
all: bin prog

# Binary, depends on the object files
bin: $(BIN)
$(BIN): $(OBJS)
	$(CL) $(CFLAGS) -o $(BIN) $(OBJS) $(LFLAGS)

# Compile the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean
clean:
	rm -fr $(BIN) $(OBJS)

prog: $(BIN)
	$(MSPDEBUG) $(MSPTYPE) "prog $(BIN)"

identify:
	@echo "Device: $(MCU)"

help:
	@echo "Target binary:"
	@echo "  $(BIN)"
	@echo
	@echo "Object files:"
	@echo "  $(OBJS)"
	@echo 
	@echo "Supported rules:"
	@echo "  all       Build and program the device"
	@echo "  bin       Only build binary"
	@echo "  prog      Only program device with binary"
	@echo "  clean     Clean the build environment"
	@echo "  identify  Identify the attached MCU"

