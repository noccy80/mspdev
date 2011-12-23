//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up/down mode. The value in TACCR0, 128, defines the
//  PWM period/2 and the values in TACCR1 and TACCR2 the PWM duty cycles. Using
//  ~1.2MHz SMCLK as TACLK, the timer period is ~212us with a 75% duty cycle
//  on P1.2 and 25% on P1.3.
//  SMCLK = MCLK = TACLK = default DCO ~1.2MHz
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> TACCR1 - 75% PWM
//           |         P1.3/TA2|--> TACCR2 - 25% PWM
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace and RTSC related includes ========
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
