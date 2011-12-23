//******************************************************************************
//  MSP430F22x4 Demo - Basic Clock, MCLK Sourced from HF XTAL
//
//  Description: Proper selection of an external HF XTAL for MCLK is shown by
//  first polling the OSC fault until XTAL is stable - only then is MCLK
//  sourced by LFXT1. MCLK/10 is on P1.1 driven by a software loop taking
//  exactly 10 CPU cycles.
//  ACLK = MCLK = LFXT1 = HF XTAL, SMCLK = default DCO ~1.2MHz
//  //* HF XTAL NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//         --|RST          XOUT|-
//           |                 |
//           |             P1.1|-->MCLK/10 = HFXTAL/10
//           |             P2.0|-->ACLK = HFXTAL
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P2DIR |= 0x01;                            // P2.0 = output direction
  P2SEL |= 0x01;                            // P2.0 = ACLK function
  P1DIR |= 0x02;                            // P1.1 = output direction

  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL
  BCSCTL3 |= LFXT1S1;                       // 3 – 16MHz crystal or resonator

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)

  for (;;)                                  // Infinite loop
  {
    P1OUT |= 0x02;                          // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}
