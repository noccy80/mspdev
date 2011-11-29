#ifndef __HUART_H__
#define __HUART_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <msp430.h>
#include <legacymsp430.h>

// Test for UCPEN here - probably not the only nor the best one
#ifndef UCPEN
#warning This device does not seem to have a hardware UART interface. Consider using suart instead of huart
#endif

#define TXD BIT1 // TXD on P1.1
#define RXD BIT2 // RXD on P1.2

#define Bit_time 104 // 9600 Baud, SMCLK=1MHz (1MHz/9600)=104
#define Bit_time_5 52 // Time for half a bit.

#define HUART_RCVBUFSIZE 32 // Size of receive buffer

int putchar(int character);
void huart_init(void);
void huart_transmit(unsigned int byte);
bool huart_datawaiting(void);
unsigned char huart_receive(void);

#endif
