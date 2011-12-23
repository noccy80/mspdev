//******************************************************************************
//  MSP430x41x2 Demo - FLL+, Output Buffered SMCLK, ACLK
//
//  Description: Buffer ACLK on P1.6 and MCLK(DCO) on P1.1.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//                MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.6|-->ACLK = 32kHz
//            |                 |
//            |             P1.1|-->MCLK = DCO
//            |                 |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize
  do
  {
    IFG1 &= ~OFIFG;                         // Clear osc fault flag
    for (i = 0; i < 1000; i++);             // Delay for osc to stabilize
  } while(IFG1 & OFIFG);                    // Check to see if osc flag is set


  P1DIR = BIT1+BIT6;                        // Set P1.6,1 as outputs
  P1SEL = BIT1+BIT6;                        // Select P1.6,1 as clk option
  while(1);                                 // Loop in place
}
