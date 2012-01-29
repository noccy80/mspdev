#
# Generic Makefile for MSP430-based projects
#
# (c) 2011, NoccyLabs.info
#
# Source files and target binary, define your source files here to have them
# compiled, and define the target basename. BUILD defines the default build
# type, as either "lib" or "bin". If bin, an .elf binary will be created as
# well as a .hex file, and if lib an .a library file will be created. To have
# the binary flashed on the device after build, use "bin prog".
#
SOURCEC   = fifo.c usci.c usi.c io.c
SOURCECPP = 
ifeq ($(WITH_HUART),1)
SOURCECPP+= usci_serial.cpp
else
SOURCEC  += suart.c
endif
BUILD     = lib
TARGET    = libcomm
INCLUDES  = -I..
LIBS      =

include ../../../skeleton/common.mk
