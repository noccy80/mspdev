//******************************************************************************
//  MSP-FET430P120 Demo - ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0
//
//  Description: Output ADC10 internal VRef on P2.4, toggling between two
//  avaialble options, 2.5v and 1.5v. ADC10OSC also output on P1.0.
//  //* MSP430F1232 or MSP430F1132 Device Required *//
//
//               MSP430F1232
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//     VRef<-|A4/P2.4      P1.0|--> ADC10OSC ~ 3.5MHz - 6.5MHz
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void delay(void);                           // Software delay

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = CONSEQ_2;                     // Repeat single channel
  ADC10CTL0 = REFOUT + REFON + MSC + ADC10ON;
  _EINT();                                  // Enable interrupts.
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  _DINT();
  ADC10AE |= 0x10;                          // P2.4 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 output direction
  P1SEL |= 0x01;                            // Set P1.0 option select

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
}// ta0_isr()
