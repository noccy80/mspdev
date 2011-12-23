//******************************************************************************
//   MSP430F23x0 Demo - Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
//
//   Description: This program generates two PWM outputs on P4.1,2 using
//   Timer_B configured for up/down mode. The value in TBCCR0, 128, defines
//   the PWM period/2 and the values in TBCCR1-2 the PWM duty cycles. Using
//   ~1.2MHz SMCLK as TBCLK, the timer period is ~213us with a 75% duty
//   cycle on P4.1 and 25% on P4.2.
//   ACLK = n/a, SMCLK = MCLK = TBCLK = default DCO ~1.2MHz
//
//                MSP430F23x0
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |         P4.1/TB1|--> TBCCR1 - 75% PWM
//            |         P4.2/TB2|--> TBCCR2 - 25% PWM
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

    __bis_SR_register(LPM0_bits);             // CPU off
}
