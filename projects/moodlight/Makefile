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

# Source files, C, C++  and Assembly
SOURCEC   = main.c bcd.c inputs.c
SOURCECPP =
SOURCEASM =

# Libraries
LIBS      = -larduino

# bin:binary file, lib:library, prog:program device
BUILD     = bin prog

# Target binary without extension.
TARGET    = main

include ../../skeleton/common.mk

# This sets all the pointers for the libraries in order.
LIB430    = ../../lib430
# Load LibArduino
include ../../skeleton/lib430.mk
