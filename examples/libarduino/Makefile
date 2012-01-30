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
SOURCEC   = main.c
SOURCECPP =
SOURCEASM =

# bin:binary file, lib:library, prog:program device
BUILD     = bin prog

# Target binary without extension.
TARGET    = arduinotest

# Include paths, f.ex. -I. -Isome/path
INCLUDES  = -I../../lib430/$(MCU)/include

# If you don't have common.mk for some reason you can manually download it from
# theNoccyLabs repository at http://sv.noccy.com/mspdev/skeleton/common.mk 
include ../../skeleton/common.mk

# Libraries to link with, f.ex. -lcomm
LIBS      = -larduino
# Specify the lib directories, f.ex. -Llib -Lsome/path
LIBPATH   =  -L../../lib430/$(MCU)/lib

