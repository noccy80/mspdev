//******************************************************************************
//   MSP430x42x0 Demo - Basic Timer, Toggle P1.0 Inside ISR, 32kHz ACLK
//
//   Description: This program toggles P1.0 by xor'ing P1.0 inside of
//   a basic timer ISR. ACLK provides basic timer clock source.
//   The output frequency is 4 Hz.
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F4270
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
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
  FLL_CTL0 |= XCAP18PF;                     // Set load cap for 32k xtal
  P1DIR |= 0x01;                            // Set P1.0 as output
  BTCTL = BTDIV + BT_fCLK2_DIV16;           // ACLK/(256*16)
  IE2 |= BTIE;                              // Enable BT interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, enable interrupts
}

// Basic Timer Interrupt Service Routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

