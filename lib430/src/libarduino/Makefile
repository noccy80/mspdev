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
SOURCEC   = arduino.c uptime.c
BUILD     = lib
TARGET    = libarduino
INCLUDES  = -I. -I.. -I../libcore -I../libcomm
LIBS      =

include ../../../skeleton/common.mk
include ../../../skeleton/install.mk

