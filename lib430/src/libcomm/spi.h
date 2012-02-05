/**
 * @file spi.h
 * @brief SPI Implementation (Header files)
 */
#ifndef __SPI_H__
#define __SPI_H__

#include <gpio.h>
#include <stdint.h>

typedef struct _SPI_SESSION {
	

} SPI_SESSION;

int spi_setup(SPI_SESSION* spisess, GPIOPIN pClock, GPIOPIN pDataInBi);
int spi_write(SPI_SESSION* spisess, uint8_t address, const char* data);
int spi_read(SPI_SESSION* spisess, uint8_t address, const char* data, uint8_t len);

#endif
