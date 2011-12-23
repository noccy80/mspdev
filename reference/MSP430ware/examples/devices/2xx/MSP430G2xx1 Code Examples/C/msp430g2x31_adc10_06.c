//******************************************************************************
//  MSP430G2x31 Demo - ADC10, Output Internal Vref on P1.4 & ADCCLK on P1.3
//
//  Description: Output ADC10 internal Vref on P1.4, toggling between two
//  avaialble options, 2.5v and 1.5v. ADC10OSC also output on P1.3.
//
//               MSP430G2x31
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//     Vref<-|A4/P1.4      P1.3|--> ADC10OSC ~ 3.5MHz - 6.5MHz
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include  "msp430g2231.h"

void delay(void);                           // Software delay

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = CONSEQ_2;                     // Repeat single channel
  ADC10CTL0 = REFOUT + REFON + MSC + ADC10ON;
  __enable_interrupt();                     // Enable interrupts.
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  __disable_interrupt();
  ADC10AE0 |= 0x10;                         // P1.4 ADC option select
  P1DIR |= 0x08;                            // Set P1.3 output direction
  P1SEL |= 0x08;                            // Set P1.3 option select

  for (;;)
  {
    ADC10CTL0 &= ~ENC;                      // ADC10 disable
    ADC10CTL0 ^= REF2_5V;                   // Toggle Vref 1.5/2.5V
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    delay();
  }
}

void delay(void)
{
  volatile unsigned long i;
    for (i = 0x7FFFF; i > 0; i--);
}

#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}
