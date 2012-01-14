#include "fifo.h"

void fifo_init(FIFO* fifo, uint8_t size) {
	fifo->size = size;
	fifo->pMem = (uint8_t*)malloc(fifo->size);
	fifo->rptr = 0;
	fifo->wptr = 0;
	fifo->len = 0;
}

uint8_t fifo_peek(FIFO* fifo) {
	return (fifo->len > 0);
}

void fifo_push(FIFO* fifo, uint8_t byte) {
	fifo->pMem[fifo->wptr++] = byte;
	if (fifo->wptr >= fifo->size - 1) {
		fifo->wptr = 0;
		fifo->len++;
	}
}

uint8_t fifo_pop(FIFO* fifo) {
	if (fifo->len==0) return 0;
	uint8_t ret = fifo->pMem[fifo->rptr++];
	if (fifo->rptr >= fifo->size - 1) {
		fifo->rptr = 0;
		fifo->len--;
	}
	return ret;
}
