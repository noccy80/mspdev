#include <cc1101.h>
#include <stdint.h>
#include <stdbool.h>
#include <spi.h>

#define CC1101_CFG_CONFIG 0
#define CC1101_CFG_PMODE 0

SPI_SESSION spisess;

int cc1101_initialize( CC1101 *radio,
	GPIOPIN pClock, GPIOPIN pDataInBi, GPIOPIN pDataOut,
	long options
) {
	// Set up the SPI connection
	//spi_setup(&spisess, pClock, pDataInBi);
	//spi_write(&spisess,CC1101_CFG_CONFIG,&CC1101_DATA_INITIAL);
	return 0;
}

int cc1101_set_callback( CC1101* radio, int cb) {
	radio->cbaddr = cb;
	return 0;
}

int cc1101_power_state( CC1101 *radio, uint8_t state ) {
	radio->state = state;
	// spi_write(&spisess,CC1101_CFG_PMODE,(const char*)state);
	return 0;
}
