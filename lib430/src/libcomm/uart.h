#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>
#include <stdint.h>


void uart_flush();

void uart_init();

void uart_transmit(unsigned int byte);

int uart_datawaiting();

unsigned char uart_receive();

#endif // __UART_H__
