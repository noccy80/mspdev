//******************************************************************************
//   MSP430FR57xx Demo - Configure MCLK for 24MHz operation
//
//   Description: Configure ACLK = SMCLK = MCLK = 24MHz
//   IMPORTANT NOTE: While the FR5739 is capable of operation using a 24MHz 
//   MCLK; the throughput of the device is dependednt on accesses to FRAM. 
//   The maximum speed for accessing FRAM is limited to 8MHz*. 
//   Wait states are inserted automatically when the FRAM is accessed at 
//   speeds higher than 8MHz to prevent timing violations.
//   Refer to the FRAM Clock System chapter of the User's Guide.
//   * Refer device D/s for typical numbers
//
//           MSP430FR57x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |               |  
//        |          P2.0 |---> ACLK = MCLk = 24MHz
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
  CSCTL1 |= DCORSEL + DCOFSEL0 + DCOFSEL1;   // Set max. DCO setting
  CSCTL2 = SELA_3 + SELS_3 + SELM_3;        // set ACLK = MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;        // set all dividers to 0
    

  P2OUT = 0;                                // output ACLK
  P2DIR |= BIT0;
  P2SEL1 |= BIT0; 
  P2SEL0 |= BIT0;
  
  while(1);
  
}
