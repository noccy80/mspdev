//******************************************************************************
//  MSP430F54x Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F5438
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  W. Goh
//  Texas Instruments, Inc
//  July 2009
//  Built with CCE v3.1 Build 3.2.3.6.4 & IAR Embedded Workbench Version: 4.20
//******************************************************************************

#include  "msp430x54x.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P1DIR |= 0x01;                        // Set P1.0 to output direction

  while(1)
  {
    P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR
    __delay_cycles(100000);
  }
}
