//******************************************************************************
//  MSP430G2xx2 Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 30ms based on default DCO/SMCLK clock source
//  used in this example for the WDT.
//  ACLK = n/a, MCLK = SMCLK = default
//
//		  MSP430G2xx2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    CSL_init();                     // Activate Grace-generated configuration

    _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

void watchdog_timer(void)
{
    P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}
