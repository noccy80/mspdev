//*******************************************************************************
//   MSP430x41x2 Demo - SVS, Toggle port 4.6 on Vcc < 2.8V
//
//  Description: The SVS feature is used to monitor VCC. LED toggles when Vcc 
//  drops below reference threshold of 2.8V.SVS flags need to be reset in
//  software.
//  
//  ACLK= n/a, MCLK= SMCLK= default DCO ~ 1.1MHz
//
//               MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//            |                 |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

int i;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= 0x02;                            // P5.1 - Set as output
  SVSCTL = VLD3;                            // SVS enabled @ 2.8V, no POR
  while(1)
  {   
    while(SVSCTL&SVSFG)
    {
      P5OUT ^= 0x02;                        // Toggle LED
      for (i = 0; i < 0x4000; i++);         // SW Delay
      SVSCTL &= ~SVSFG;
    }
  }
}
