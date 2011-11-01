#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>
#include <msp430.h>
#include <legacymsp430.h>

volatile uint16_t systick = 0;

void delay_ms(uint16_t n);
void flash(int8_t led, int8_t times, uint16_t duration);

#endif // __UTILS_H__
