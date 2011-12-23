//******************************************************************************
//  MSP430x41x2 Demo - Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
//
//  Description: Toggles P5.1 by xor'ing P5.1 inside of a basic timer ISR.
//  SMCLK provides the basic timer clock source. When using default FLL+
//  register settings and an external 32kHz watch crystal, LED toggles
//  every ~244us.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//               MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//*****************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load cap for 32k xtal
  P5DIR |= 0x02;                            // Set P5.1 as output
  BTCTL = BTSSEL + BT_fCLK2_DIV256;         // SMCLK/256
  IE2 |= BTIE;                              // Enable BT interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
}

// Basic Timer Interrupt Service Routine
#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer_ISR(void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1
}

