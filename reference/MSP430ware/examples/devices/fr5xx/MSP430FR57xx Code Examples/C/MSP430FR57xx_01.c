//******************************************************************************
//  MSP430FR57x Demo - Toggle P1.0 using software
//
//  Description: Toggle P1.0 using software.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO = ~625 KHz
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  
 
  P1DIR |= BIT0;
  P1OUT |= BIT0;
  
  while(1)
  {
      P1OUT ^= BIT0;
      __delay_cycles(100000);
  }
}
