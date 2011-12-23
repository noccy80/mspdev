//******************************************************************************
//  MSP430xG46x Demo - Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P5.1 using software and the TA_0 ISR. Timer_A is
//  configured for up mode, thus the the timer overflows when TAR counts
//  to TACCR0. In this example, TACCR0 is loaded with 1000-1. LED toggles every
//  30.5ms.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//           MSP430xG461x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
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

  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = 1000-1;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
    P5OUT ^= 0x02;                          // Toggle P5.1 using exclusive-OR
}

