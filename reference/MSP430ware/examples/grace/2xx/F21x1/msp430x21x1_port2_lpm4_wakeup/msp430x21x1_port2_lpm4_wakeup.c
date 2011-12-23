//******************************************************************************
//  MSP430x11x1 Demo - Software Port Interrupt Service on P2.0 from LPM4
//
//  Description: A hi/low transition on P2.0 will trigger P2_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//  with the LED removed, all unused P1.x/P2.x configured as output or inputs
//  pulled high or low, and ensure the P2.0 interrupt input does not float.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k
//
//                MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--| P2.0        P1.0|-->LED
//     \|/
//*****************************************************************************
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

    _BIS_SR(LPM4_bits + GIE);             // Enter LPM4 w/interrupt
}

void Port_2(void)
{
    P1OUT ^= 0x01;                        // P1.0 = toggle
    P2IFG &= ~0x01;                       // P2.0 IFG clearedf
}
