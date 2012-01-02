#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <msp430.h>
#include <legacymsp430.h>
#include "ta0compat.h"
#include <stdint.h>

#define  LED_DIR   P1DIR
#define  LED_OUT   P1OUT

#define BTN_DIR P2DIR
#define BTN_IN P2IN

#define LED_MENU BIT0
#define SENSE_DATA BIT3
#define SENSE_CLOCK BIT4
#define BTN_MENU BIT1
#define BTN_NEXT BIT2

#endif // __CONFIG_H__
