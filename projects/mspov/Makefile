# Source files and target binary, define your source files here to have them
# compiled, and define the target basename. An .elf binary will be created as
# well as a .hex file:
SOURCES  = main.c database.c config.c
SOURCESA =
TARGET   = mspov

include ../../skeleton/common.mk

LIBS     = -L../../lib430/$(MCU)/lib
INCLUDES = -I../../lib430/$(MCU)/include
LIBS    += -lair

