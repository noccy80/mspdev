#include "cc1101.h"
#include <libcomm.h>
#include <libusi.h>
#include <stdint.h>
#include <stdbool.h>
#include <spi.h>

int cc1101_initialize( CC1101 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	long options
);
int cc1101_power_state( CC1101 *radio, uint8_t state );
int cc1101_set_callback( CC1101 *radio, (void*)cb );

SPI_CONNECTION spisess;

int cc1101_initialize( CC1101 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	long options
) {
	// Set up the SPI connection
	spi_setup(&spisess, pClock, pDataInBi);
	spi_write(&spisess,CC1101_CFG_CONFIG,CC1101_DATA_INITIAL);
}

int cc1101_set_callback( CC1101 *radio, (void*)cb ) {
	radio->cbaddr = cb;
}

int cc1101_power_state( CC1101 *radio, uint8_t state ) {
	radio->state = state;
	spi_write(&spisess,CC1101_CFG_PMODE,state);
}
