//*******************************************************************************
//  MSP430x24x Demo - Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  ~1.045Mhz SMCLK as TACLK, the timer period is ~233us with a 75% duty cycle
//  on P1.2 and 25% on P1.3.
//  SMCLK = MCLK = TACLK = default DCO ~1.045Mhz.
//
//               MSP430F249
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//           |         P1.3/TA2|--> CCR2 - 25% PWM
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

    _BIS_SR(CPUOFF);                          // Enter LPM0
}

void Timer_A(void)
{
}
