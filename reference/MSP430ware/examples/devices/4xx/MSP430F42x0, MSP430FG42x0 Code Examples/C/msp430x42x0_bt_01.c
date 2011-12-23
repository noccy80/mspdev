//******************************************************************************
//   MSP430x42x0 Demo - Basic Timer, Toggle P1.0 Inside ISR, DCO SMCLK
//
//   Description: This program toggles P1.0 by xor'ing P1.0 inside of
//   a basic timer ISR. SMCLK provides basic timer clock source.
//   The output frequency is 2.048 KHz.
//   ACLK = n/a, MCLK = SMCLK = default DCO
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F4270
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  L. Westlund / S. Karthikeyan
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************
#include  <msp430x42x0.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Set load cap for 32k xtal
  P1DIR |= 0x01;                            // Set P1.0 as output
  BTCTL = BTSSEL + BT_fCLK2_DIV256;         // SMCLK/256
  IE2 |= BTIE;                              // Enable BT interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, enable interrupts
}

// Basic Timer Interrupt Service Routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

