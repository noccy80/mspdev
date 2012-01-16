# Source files and target binary, define your source files here to have them
# compiled, and define the target basename. An .elf binary will be created as
# well as a .hex file:
SOURCES  = ui.c
SOURCESA =
TARGET   = ui

include common.mk

INCLUDES = -I../../../lib430/$(MCU)/include
LIBS     = -L../../../lib430/$(MCU)/lib -lcomm
