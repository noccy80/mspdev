File structure 

Master - Files needed for I2C master device
  
  |--Example - Application files to access master library
      |------ASM
               |--------example_EEPROM.s43 - Application file to interface with slave EEPROM device
               |--------example_master430interface.s43 - Application file to interface with slave MSP430  device (use with example_slave430interface.s43)
      |------C
               |--------example_EEPROM.c - Application file to interface with slave EEPROM device
               |--------example_master430interface.c - Application file to interface with slave MSP430 device (use with example_slave430interface.s43)
  |--Source Code
      |------USI_I2CMaster.s43 - Library file for I2C master
      |------USI_I2CMaster.h - Header file for I2C master

Slave - Files needed for I2C slave device
  |--Example - Application file to access slave library
      |------ASM
               |--------example_slave430interface.s43 - Application file to interface with master MSP430  device (use with example_master430interface.s43)
      |------C
               |--------example_slave430interface.c - Application file to interface with master MSP430 device (use with example_master430interface.s43)
  |--Source Code
      |------USI_I2CSlave.s43 - Library file for I2C slave
      |------USI_I2CSlave.h - Header file for I2C slave