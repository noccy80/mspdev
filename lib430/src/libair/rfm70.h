s#ifndef __RFM70_H__
#define __RFM70_H__

#include <spi.h>

int rfm70_initialize( RFM70 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	long options
);
int rfm70_power_state( RFM70 *radio, uint8_t state );
int rfm70_set_callback( RFM70 *radio );

unsigned int rfm70_get_register( RFM70* radio , unsigned int register);



SPI_SESSION spisess;

#endif
