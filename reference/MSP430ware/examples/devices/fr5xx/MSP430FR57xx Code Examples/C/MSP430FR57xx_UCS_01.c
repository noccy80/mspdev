//******************************************************************************
//   MSP430FR57xx Demo - Configure MCLK for 8MHz operation
//
//   Description: Configure ACLK = SMCLK = MCLK = 8MHz
// 
//           MSP430FR57x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |               |  
//        |          P2.0 |---> ACLK = MCLk = 8MHz
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
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_3 + SELS_3 + SELM_3;        // set ACLK = MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;        // set all dividers 
    

  P2OUT = 0;                                // output ACLK
  P2DIR |= BIT0;
  P2SEL1 |= BIT0; 
  P2SEL0 |= BIT0;
  
  while(1);
  
}
