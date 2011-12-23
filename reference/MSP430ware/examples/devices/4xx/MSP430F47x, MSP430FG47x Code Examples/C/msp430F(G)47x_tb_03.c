//******************************************************************************
//  MSP430F(G)47x Demo - Timer_B, Toggle P4.6, Overflow ISR, DCO SMCLK
//
//  Description: This program toggles P4.6 using software and the Timer_B
//  overflow ISR. In this example an ISR triggers when TB overflows.
//  Inside the ISR P4.6 is toggled.  Toggle rate is 16Hz when using default
//  FLL+ register settings and an external 32kHz watch crystal.
//  Proper use of TBIV interrupt vector generator is demonstrated.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//           MSP430F(G)47x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P4DIR |= 0x40;                            // Set P4.6 to output direction
  TBCTL = TBSSEL1 + TBCLR + TBIE;           // SMCLK, clr. TBR, interrupt
  TBCTL |= MC1;                             // Start Timer_B in continous
  TBCTL = TBSSEL_2 + MC_2 + TBIE;           // SMCLK, contmode, interrupt

  __bis_SR_register(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_B7 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
 switch( TBIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 14: P4OUT ^= 0x40;                  // overflow
            break;
 }
}

