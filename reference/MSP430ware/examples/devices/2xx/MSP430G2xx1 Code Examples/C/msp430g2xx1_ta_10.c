//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
//
//  Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
//  for up mode with CCR0 defining period, TA0 also output on P1.1. In this
//  example, CCR0 is loaded with 500-1 and TA0 will toggle P1.1 at TACLK/500.
//  Thus the output frequency on P1.1 will be the TACLK/1000. No CPU or
//  software resources required.
//  ACLK = n/a, SMCLK = MCLK = TACLK = default DCO
//  As coded with TACLK = SMCLK, P1.1 output frequency is ~1000000/1000
//
//            MSP430G2xx1
//         -----------------
//     /|\|              XIN|-
//      | |                 |
//      --|RST          XOUT|-
//        |                 |
//        |         P1.1/TA0|--> SMCLK/1000
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x02;                            // P1.1 output
  P1SEL |= 0x02;                            // P1.1 option select
  CCTL0 = OUTMOD_4;                         // CCR0 toggle mode
  CCR0 = 500-1;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  _BIS_SR(CPUOFF);                          // CPU off
}
