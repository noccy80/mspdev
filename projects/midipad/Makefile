# Source files and target binary, define your source files here to have them
# compiled, and define the target basename. An .elf binary will be created as
# well as a .hex file:
SOURCES  = main.c flash.c
SOURCESA =
BUILD    = bin prog
TARGET   = midipad

include ../../skeleton/common.mk

LIBS     = -L../../lib430/$(MCU)/lib
INCLUDES = -I../../lib430/$(MCU)/include
LIBS    += -lmidi

