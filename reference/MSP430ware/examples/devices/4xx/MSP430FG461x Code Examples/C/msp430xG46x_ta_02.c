//******************************************************************************
//  MSP430xG46x Demo - Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P5.1 using software and TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to TACCR0. In this example, TACCR0 is loaded with 20000.
//  ACLK = 32.768kHz, MCLK = SMCLK = TACLK = Default DCO
//
//           MSP430xG461x
//         ---------------
//     /|\|            XIN|-
//      | |               |   32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P5DIR |= 0x02;                            // P5.1 output
  TACCTL0 = CCIE;                             // TACCR0 interrupt enabled
  TACCR0 = 20000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1 using exclusive-OR
}

