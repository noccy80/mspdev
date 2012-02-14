# -*- mode: makefile-gmake; mode: flyspell; -*-

# Makefile for calibrate DCO oscillator

TARGET=calibrate_dco

# Options may be specified by OPTION variable in command line.
#
# WRITE_TO_FLASH
#   if you want to erase the Segment A flash and write the calibrated
#   value into Segment A.
#
# USE_ROSC
#   if you want to use external Rosc.
#
# LFXT1_HZ=<frequency_in_hz>
#   if you want to use the XTAL for LFXT1 other than 32.768kHz
#
# FREQn_KHZ=<nth_calibration_frequency_in_khz>
#   if you want to alter the calibration frequency. n=2..4

# For example
#
#   make msp430f2132 OPTION='WRITE_TO_FLASH LFXT1=32768' ERRATA='BCL12 XOSC8'
# 
# will make calibrate_dco which writes calibrated values of DCO, using
# 32768kHz LFXT1 xtal, onto Segment A flash for msp430f2131, which has
# errata BCL12 and XOSC8.

default: msp430f2013

msp430%:
ifneq ($(ERRATA),)
	$(MAKE) clean $(TARGET).hex MCU=$@ ERRATA="$(ERRATA)"
else
	$(MAKE) clean $(TARGET).hex MCU=$@ ERRATA="$(ERRATA_$@)"
endif

# Default silicon errata table
ERRATA_msp430f1121=BCL5
ERRATA_msp430f1132=BCL5
ERRATA_msp430f1232=BCL5
ERRATA_msp430f1611=BCL5
ERRATA_msp430f1612=BCL5
ERRATA_msp430f2012=BCL12 XOSC8
ERRATA_msp430f2013=BCL12
ERRATA_msp430f2131=BCL12
ERRATA_msp430f2132=BCL12 XOSC8
ERRATA_msp430f2274=BCL12
ERRATA_msp430g2211=BCL12 XOSC8
ERRATA_msp430g2231=BCL12 XOSC8
ERRATA_msp430f2618=BCL12

CC=msp430-gcc
CFLAGS+=-Os -Wall -mmcu=$(MCU)
LDFLAGS+=-mmcu=$(MCU) -mdisable-watchdog
OBJCOPY=msp430-objcopy

ifneq ($(OPTION),)
CFLAGS+=$(foreach _opt,$(OPTION),$(patsubst %,-D%,$(_opt)))
endif

ifneq ($(ERRATA),)
CFLAGS+=$(foreach _errata,$(ERRATA),$(patsubst %,-DERRATA_%,$(_errata)))
endif

calibrate_dco: calibrate_dco.o flash.o dco.o copy.o

%.hex : %
	$(OBJCOPY) --output-target=ihex $< $@

clean:
	-rm -f *~ *.o $(TARGET) $(TARGET).hex

.PHONY: clean

# vim: set noet ts=8 sw=8:
