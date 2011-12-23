//******************************************************************************
//  MSP430x41x2 Demo - Software Poll P1.4, Set P5.1 if P1.4 = 1
//
//  Description: Poll P1.4 in a loop, if high P5.1 is set, else P5.1 is reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//              MSP430x41x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P5.1|-->LED
//     \|/
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  while (1)                                 // Test P1.4
  {
    if (0x010 & P1IN)
      P5OUT |= 0x02;                        // if P1.4 set, set P5.1
    else
      P5OUT &= ~0x02;                       // else reset
  }
}


