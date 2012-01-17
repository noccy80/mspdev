#ifndef __RFM70_H__
#define __RFM70_H__

#include <spi.h>

int rfm70_initialize( CC1101 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	long options
);
int rfm70_power_state( CC1101 *radio, uint8_t state );
int rfm70_set_callback( CC1101 *radio );

SPI_SESSION spisess;

#endif
