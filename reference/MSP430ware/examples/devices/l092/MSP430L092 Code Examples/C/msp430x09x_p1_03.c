//******************************************************************************
//  MSP430x09x Demo - Poll P1 With Software with Internal Pull-up
//
//  Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  Internal pullup enabled on P1.3.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430x09x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.3-o      P1.0|-->Output
//     \|/
//
//  D.Dang/ D.Archbold/ D.Szmulewicz                                           
//  Texas Instruments Inc.                                                 
// Built with IAR Version 5.10.4                                                    
//****************************************************************************
#include "msp430l092.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = BIT0;                             // P1.0 output, else input
  P1OUT = BIT3;                             // P1.3 pullup
  P1REN |= BIT3;                            // P1.3 pullup

  while (1)                                 // Test P1.3
  {
    if (BIT3 & P1IN)
      P1OUT |= BIT0;                        // if P1.3 set, set P1.0
    else
      P1OUT &= ~BIT0;                       // else reset
  }
}


