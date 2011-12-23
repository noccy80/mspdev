//******************************************************************************
//  MSP430x09x Demo - Software Poll P1.3, Set P1.0 if P1.3 = 1
//
//  Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430x09x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.3         P1.0|-->Output
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
  P1DIR |= BIT0;                            // Set P1.0 to output direction

  while (1)                                 // Test P1.3
  {
    if (BIT3 & P1IN)
      P1OUT |= BIT0;                        // if P1.3 set, set P1.0
    else
      P1OUT &= ~BIT0;                       // else reset
  }
}


