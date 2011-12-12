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
# Define the MCU if not set
MCU?=msp430g2553
#
# Source files and target library, define your source files here to have them
# compiled, and define the target basename. 
SOURCES  = Application/Application.c \
	Application/Callback.c \
	Application/CommandInterface.c \
	Application/main.c \
	Application/Protocol.c \
	Application/RadioOperation.c \
	Framework/FPI/Devices/COMPort/COMPortInterface.c \
	Framework/FPI/Devices/LED/LEDInterface.c \
	Framework/FPI/Devices/Radio/CCXXX/Interface/CC1101Interface.c \
	Framework/FPI/Devices/Radio/CCXXX/CCXXXInterface.c \
	Framework/FPI/Devices/Radio/RadioInterface.c \
	Framework/FPI/FPI.c \
	Framework/MCU/MSP430/Peripherals/Architecture/BasicClockSystemPlus.c \
	Framework/MCU/MSP430/Peripherals/Communication/USCI.c \
	Framework/MCU/MSP430/Peripherals/DataConverter/ADC10.c \
	Framework/MCU/MSP430/Peripherals/GPIO/DigitalIO.c \
	Framework/MCU/MSP430/Peripherals/Timer/TimerA.c \
	Framework/MCU/MSP430/Peripherals/Timer/WatchdogTimerPlus.c \
	Framework/MCU/MSP430/Analog.c \
	Framework/MCU/MSP430/Architecture.c \
	Framework/MCU/MSP430/Communication.c \
	Framework/MCU/MSP430/DataConverter.c \
	Framework/MCU/MSP430/GPIO.c \
	Framework/MCU/MSP430/LCD.c \
	Framework/MCU/MSP430/SpecialModule.c \
	Framework/MCU/MSP430/Timer.c \
	Framework/MCU/MCUInterface.c \
SOURCESA =
TARGET   = libAir
INCLUDES =
LIBS     =
#
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
.phony: all lib clean

# All, to build the binary and program it
all: lib

# Binary, depends on the object files
lib: $(TARGET).lib

$(TARGET).lib: $(OBJS)
ifeq ($(MCU),)
	@echo "ERROR: MCU not defined or programmer not connected."
	@echo $(MCU)
	@exit 1
endif
	$(CC) $(LDFLAGS) -o $(TARGET).elf $(OBJS) $(LIBS)
	$(SIZE) $(TARGET).elf

# Compile the object files
%.o: %.c
ifeq ($(MCU),)
	@echo "ERROR: MCU not defined or programmer not connected."
	@echo $(MCU)
	@exit 1
endif
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.asm
ifeq ($(MCU),)
	@echo "ERROR: MCU not defined or programmer not connected."
	@exit 1
endif
	$(CC) -c $(ASFLAGS) -o $@ $<

# Clean
clean:
	rm -fr $(TARGET).lib $(TARGET).a $(TARGET).elf $(TARGET).map $(OBJS) $(LSTS)

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
	@echo "  package   Create tarball package"


