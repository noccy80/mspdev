//******************************************************************************
//   MSP430xG46x Demo - Timer_B, Toggle P5.1, TBCCR0 Up Mode ISR, 32kHz ACLK
//
//   Description: Toggle P5.1 using software and the TB_0 ISR. Timer_B is
//   configured for up mode, thus the timer overflows when TBR counts to TBCCR0.
//   In this example, TBCCR0 is loaded with 1000-1.
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430xG46x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P5DIR |= 0x002;                           // P5.1 output

  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 1000-1;                          // TBCCR0 counts to 1000
  TBCTL = TBSSEL_1+MC_1;                    // ACLK, upmode

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}

// Timer_B interrupt service routine -- Toggle P5.1
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1
}

