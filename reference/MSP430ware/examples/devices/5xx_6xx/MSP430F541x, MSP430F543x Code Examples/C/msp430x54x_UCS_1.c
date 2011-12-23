//******************************************************************************
//   MSP430F54x Demo - Software Toggle P1.0 at Default DCO
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK is rought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK
//   is brought out on pin P11.1.
//   ACLK = REFO = 32.768kHz, MCLK = SMCLK = (Default DCO)/2 = (2MHz/2) = 1MHz
//
//                 MSP430F5438
//             -----------------
//         /|\|                 |
//          | |            P11.0|-->ACLK
//          --|RST         P11.1|-->MCLK
//            |            P11.2|-->SMCLK
//            |                 |
//            |             P1.0|-->LED
//
//   W. Goh
//   Texas Instruments Inc.
//   November 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= BIT0;                            // P1.0 output
  P11DIR |= 0x07;                           // ACLK, MCLK, SMCLK set out to pins
  P11SEL |= 0x07;                           // P11.0,1,2 for debugging purposes.

  while(1)
  {
    P1OUT ^= BIT0;                          // Toggle P1.0
    __delay_cycles(60000);                  // Delay
  }
}
