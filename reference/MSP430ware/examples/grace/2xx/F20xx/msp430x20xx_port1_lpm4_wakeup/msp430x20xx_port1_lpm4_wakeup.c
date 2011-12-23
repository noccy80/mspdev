//******************************************************************************
//  MSP430F20xx Demo - P1 Interrupt from LPM4 with Internal Pull-up
//
//  Description: A hi/low transition on P1.3 will trigger P1_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA.
//  Internal pullup enabled on P1.3.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F20xx
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.3-o      P1.0|-->LED
//     \|/
//
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
void main(int argc, char *argv[])
{
    CSL_init();
    _BIS_SR(LPM4_bits + GIE);                 // Enter LPM4 w/interrupt
}
void Port_1(void)
{
	  P1OUT ^= 0x01;                            // P1.0 = toggle
	  P1IFG &= ~0x08;                           // P1.3 IFG cleared
}
