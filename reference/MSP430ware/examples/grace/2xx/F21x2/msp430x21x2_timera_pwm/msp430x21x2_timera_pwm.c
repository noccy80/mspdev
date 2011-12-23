//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, PWM TA1-1, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates PWM output P3.7 using
//  Timer1_A2 configured for up/down mode. The value in TA1CCR0, 128, defines the
//  PWM period/2 and the value in TA1CCR1 the PWM duty cycle. Using
//  ~1.2MHz SMCLK as TA1CLK, the timer period is ~212us with a 75% duty cycle
//  on P3.7
//  SMCLK = MCLK = TACLK = default DCO ~1.2MHz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |       P3.7/TA1_1|--> TACCR1 - 75% PWM
//           |                 |
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

    __bis_SR_register(LPM0_bits);             // Enter LPM0
}
