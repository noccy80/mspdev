//******************************************************************************
//  MSP430F20x2 Demo - ADC10, Sample A11, Lo_Batt, Set P1.0 if < 2.3V
//
//  Description: A single sample is made on A11 (AVcc/2) with reference to
//  internal 1.5V Vref. Software sets ADC10SC to start sample and conversion
//  - ADC10SC automatically cleared at EOC. ADC10 internal oscillator times
//  sample (16x) and conversion. ADC10BUSY flag is polled for EOC. If A11
//  (AVcc/2) < 0311h (0.65V) indicating AVcc is less 2.3V, P1.0 set indicating
//  a lo_Batt condition, else reset.
//
//                MSP430F20x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A11          P1.0|-->LED
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
    for (;;)
    {
      ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
      while (ADC10CTL1 & ADC10BUSY);          // ADC10BUSY?
      if (ADC10MEM < 0x311)                   // ADC10MEM = A11 > 0.65?
        P1OUT |= 0x01;                        // Set P1.0 LED on
      else
        P1OUT &= ~0x01;                       // Clear P1.0 LED off
    }

}
