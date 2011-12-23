//*******************************************************************************
//  MSP430F471xx Demo - SVS, Toggle port 5.1 on Vcc < 2.8V
//
//  Description: The SVS feature is used to monitor VCC. LED toggles when Vcc 
//  drops below reference threshold of 2.8V.SVS flags need to be reset in
//  software.
//  
//  ACLK= n/a, MCLK= SMCLK= default DCO ~ 1.1MHz
//
//                MSP430F471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//            |                 |
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>
int i;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= BIT1;                            // P5.1 - Set as output
  SVSCTL = VLD3;                            // SVS enabled @ 2.8V, no POR
  while(1)
  {   
    while(SVSCTL&SVSFG)
    {
      P5OUT ^= BIT1;                        // Toggle LED
      for (i = 0; i < 0x4000; i++);         // SW Delay
    }
  }
}
