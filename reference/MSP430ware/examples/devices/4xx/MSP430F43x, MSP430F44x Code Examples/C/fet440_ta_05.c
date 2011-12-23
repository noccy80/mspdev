//******************************************************************************
//  MSP-FET430P440 Demo - Timer_A, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P5.1 using software and the TA_0 ISR. Timer_A is
//  configured for up mode, thus the the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1. LED toggles every
//  30.5ms.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//           MSP430F449
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include <msp430x44x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 1000-1;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
    P5OUT ^= 0x02;                          // Toggle P5.1 using exclusive-OR
}

