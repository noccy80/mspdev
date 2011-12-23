//******************************************************************************
//  MSP430x41x2 Demo - ADC10, Output Internal Vref on P6.4 & ADCCLK on P4.7
//
//  Description: Output ADC10 internal Vref on P6.4, toggling between two
//  available options, 2.5V and 1.5V. ADC10OSC also output on P4.7.
//
//               MSP430x41x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |    P4.7/ADC10CLK|--> ADC10OSC ~ 3.5MHz - 6.5MHz
//           |          P6.4/A4|--> Vref
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

void delay(void);                           // Software delay

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = CONSEQ_2;                     // Repeat single channel
  ADC10CTL0 = REFOUT + REFON + MSC + ADC10ON;
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt
  TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode
  __bis_SR_register(CPUOFF + GIE);          // LPM0, TA0_ISR will force exit
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  ADC10AE0 |= 0x10;                         // P6.4 ADC option select
  P4DIR |= 0x80;                            // Set P4.7 output direction
  P4SEL |= 0x80;                            // Set P4.7 option select

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

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  LPM0_EXIT;                                // Exit LPM0 on return
}
