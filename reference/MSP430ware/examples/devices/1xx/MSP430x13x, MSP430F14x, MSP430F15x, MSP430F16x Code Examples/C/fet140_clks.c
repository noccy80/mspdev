//******************************************************************************
//  MSP-FET430P140 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK
//
//  Description: Output buffered MCLK, SMCLK and ACLK.
//  ACLK = LFXT1 = 32768, MCLK = DCO Max, SMCLK = XT2
//  //* XTAL's REQUIRED - NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
//
//                MSP430F149
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32k
//         --|RST          XOUT|-
//           |                 |
//           |            XT2IN|-
//           |                 | XTAL (455k - 8Mhz)
//           |RST        XT2OUT|-
//           |                 |
//           |             P5.4|-->MCLK = DCO Max
//           |             P5.5|-->SMCLK = XT2
//           |             P5.6|-->ACLK = 32kHz
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
  BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
  BCSCTL2 |= SELS;                          // SMCLK = XT2
  P5DIR |= 0x70;                            // P5.6,5,4 outputs
  P5SEL |= 0x70;                            // P5.6,5,5 options

  while(1)
  {
  }
}

