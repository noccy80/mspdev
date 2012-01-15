#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdlib.h>
#include <stdint.h>
#include <libhal/hal.h>

typedef struct _FIFO {
	uint8_t* pMem;
	uint8_t size;
	uint8_t rptr;
	uint8_t wptr;
	uint8_t len;
} FIFO;

void fifo_init(FIFO* fifo, uint8_t size);
uint8_t fifo_peek(FIFO* fifo);
void fifo_push(FIFO* fifo, uint8_t byte);
uint8_t fifo_pop(FIFO* fifo);

#endif
