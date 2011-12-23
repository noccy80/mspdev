//******************************************************************************
//   CC430F613x Demo - Software Toggle P1.0 at Default DCO
//
//   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//   ACLK is rought out on pin P2.0, SMCLK is brought out on P2.4, and MCLK
//   is brought out on pin P2.2.
//   ACLK = REFO = 32.768kHz, MCLK = SMCLK = (Default DCO)/2 = (2MHz/2) = 1MHz
//
//                 CC430F6137
//             -----------------
//         /|\|                 |
//          | |             P2.0|-->ACLK
//          --|RST          P2.2|-->MCLK
//            |             P2.4|-->SMCLK
//            |                 |
//            |             P1.0|-->LED
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_ACLK;                         // Map ACLK output to P2.0 
  P2MAP2 = PM_MCLK;                         // Map MCLK output to P2.2 
  P2MAP4 = PM_SMCLK;                        // Map SMCLK output to P2.4 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0 + BIT2 + BIT4;              // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0 + BIT2 + BIT4;              // P2.0,2,4 for debugging purposes.

  P1DIR |= BIT0;                            // P1.0 output

  while(1)
  {
    P1OUT ^= BIT0;                          // Toggle P1.0
    __delay_cycles(60000);                  // Delay
  }
}
