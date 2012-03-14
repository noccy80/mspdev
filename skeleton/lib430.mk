# To use this include, define LIB430 and have it point to the location where
# lib430 is located. Don't forget to define LIBS for it to link as well.

INCLUDES  = -I$(LIB430)/$(MCU)/include
LIBPATH   = -L$(LIB430)/$(MCU)/lib
CFLAGS   += $(shell cat $(LIB430)/$(MCU)/CXXFLAGS)
