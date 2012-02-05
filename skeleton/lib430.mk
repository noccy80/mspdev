# To use this include, define LIB430 and have it point to the location whhere
# lib430 is located. Don't forget to define LIBS for it to link as well.

INCLUDES  = -I$(LIB430)/$(MCU)/include
LIBPATH   = -L$(LIB430)/$(MCU)/lib

