//******************************************************************************
//  MSP430F23x0 Demo - Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
//  for up/down mode with TACCR0 defining period, TA0 also output on P1.1. In
//  this example, TACCR0 is loaded with 250 and TA0 will toggle P1.1 at
//  TACLK/2*250. Thus the output frequency on P1.1 will be the TACLK/1000.
//  No CPU or software resources required.
//  ACLK = n/a, SMCLK = MCLK = TACLK = default DCO ~1.2MHz
//  As coded with TACLK = SMCLK, P1.1 output frequency is ~1200000/1000
//
//           MSP430F23x0
//         -----------------
//     /|\|              XIN|-
//      | |                 |
//      --|RST          XOUT|-
//        |                 |
//        |         P1.1/TA0|--> SMCLK/1000
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
void main(int argc, char *argv[])
{
    CSL_init();

    __bis_SR_register(CPUOFF);                // CPU off
}
