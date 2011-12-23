//*******************************************************************************
//   MSP430F(G)47x Demo - SVS, Toggle port 4.6 on Vcc < 2.8V
//
//  Description: The SVS feature is used to monitor VCC. LED toggles when Vcc 
//  drops below reference threshold of 2.8V.SVS flags need to be reset in
//  software.
//  
//  ACLK= n/a, MCLK= SMCLK= default DCO ~ 1.1MHz
//
//               MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |           P4.6|-->LED
//            |                 |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h"

int i;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P4DIR |= BIT6;                            // P4.6 - Set as output
  SVSCTL = VLD3;                            // SVS enabled @ 2.8V, no POR
  while(1)
  {   
    while(SVSCTL&SVSFG)
    {
      P4OUT ^= BIT6;                        // Toggle LED
      for (i = 0; i < 0x4000; i++);         // SW Delay
      SVSCTL &= ~SVSFG;
    }
  }
}
