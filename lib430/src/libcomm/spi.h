#ifndef __SPI_H__
#define __SPI_H__

typedef struct _SPI_SESSION {
	

} SPI_SESSION;

int spi_setup(SPI_SESSION* spisess, PORTPIN pClock, PORTPIN pDataInBi);
int spi_write(SPI_SESSION* spisess, uint8_t* data);
int spi_read(SPI_SESSION* spisess, uint8_t* data, uint8_t len);

#endif
