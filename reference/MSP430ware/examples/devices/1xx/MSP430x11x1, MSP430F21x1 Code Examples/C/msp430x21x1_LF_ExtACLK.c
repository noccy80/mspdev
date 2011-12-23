//******************************************************************************
//  MSP430x21x1 Demo - LF Mode Ext Digital Clk source
//
//  Description: Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
//  P1.1. To measure SMCLK on P1.4 with the FET, use "Release JTAG on Go"
//  in the debugger to have access to the port. Then run the code.
//  ACLK = LFXT1 = Ext Clk, MCLK = SMCLK = default DCO ~1.16MHz	
//
//                MSP430F21x1
//             -----------------
//         /|\|              XIN|<--LF Ext ACLK (10-50 kHz)
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |       P1.4/SMCLK|-->SMCLK = ~1.16MHz
//            |             P1.1|-->MCLK/10 = DCO/10
//            |        P2.0/ACLK|-->ACLK = LF Ext ACLK
//
//  H. Grewal / A. Dannenberg
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include <msp430x21x1.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  BCSCTL3 |= LFXT1S_3;                      // Ext Digital Clk
  P1DIR |= 0x12;                            // P1.1 and P1.4 outputs
  P1SEL |= 0x10;                            // P1.4 SMCLK output
  P2DIR |= 0x01;                            // P2.0 output
  P2SEL |= 0x01;                            // P2.0 ACLK output

  while(1)
  {
    P1OUT |= 0x02;    	                    // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}

