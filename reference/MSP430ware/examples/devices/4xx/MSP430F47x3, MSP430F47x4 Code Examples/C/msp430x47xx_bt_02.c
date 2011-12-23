//******************************************************************************
//  MSP430x47xx Demo - Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
//
//  Description: Toggles P5.1 by xor'ing P5.1 inside of a basic timer ISR.
//  SMCLK provides the basic timer clock source. When using default FLL+
//  register settings and an external 32kHz watch crystal, LED toggles
//  every ~244us.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430x47xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//*****************************************************************************
#include  <msp430x47x4.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load cap for 32k xtal
  P5DIR |= BIT1;                            // Set P5.1 as output
  BTCTL = BTSSEL + BT_fCLK2_DIV256;         // SMCLK/256
  IE2 |= BTIE;                              // Enable BT interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0, enable interrupts
}

// Basic Timer Interrupt Service Routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
  P5OUT ^= BIT1;                            // Toggle P5.1
}

