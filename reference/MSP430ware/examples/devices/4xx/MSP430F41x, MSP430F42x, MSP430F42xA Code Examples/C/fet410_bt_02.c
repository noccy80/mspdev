//******************************************************************************
//  MSP-FET430P440 Demo - Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
//
//  Description: Toggles P5.1 by xor'ing P5.1 inside of a basic timer ISR.
//  ACLK provides the basic timer clock source. LED toggles every 125ms.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F413
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x41x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load cap for 32k xtal
  P5DIR |= 0x02;                            // Set P5.1 as output
  BTCTL = BTDIV + BT_fCLK2_DIV16;           // ACLK/(256*16)
  IE2 |= BTIE;                              // Enable BT interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, enable interrupts
}

// Basic Timer Interrupt Service Routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1
}

