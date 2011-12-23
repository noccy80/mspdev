//******************************************************************************
//  MSP430G2xx2 Demo - Timer_A, PWM TA1, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates one PWM output on P1.2 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the PWM
//  period/2 and the value in CCR1 the PWM duty cycles.
//  A 75% duty cycle is on P1.2.
//  SMCLK = MCLK = TACLK = default DCO
//
//               MSP430G2xx2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
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

    _BIS_SR(LPM0_bits);                       // Enter LPM0
}
