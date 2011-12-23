//******************************************************************************
//  MSP430x11x1 Demo - Basic Clock, MCLK Sourced from HF XTAL
//
//  Description: Proper selection of an external HF XTAL for MCLK is shown by
//  first polling the OSC fault until XTAL is stable - only then is MCLK
//  sourced by LFXT1.  MCLK/10 is on P1.1 driven by a software loop taking
//  exactly 10 CPU cycles.
//  ACLK = MCLK = LFXT1 = HF XTAL
//  //* HF XTAL NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//               MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (455k - 8Mhz)
//         --|RST          XOUT|-
//           |                 |
//           |             P1.1|-->MCLK/10 = HFXTAL/10
//           |             P2.0|-->ACLK = HFXTAL
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include <msp430x11x1.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL
  P2DIR |= 0x01;                            // P2.0 = output direction
  P2SEL |= 0x01;                            // P2.0 = ACLK function
  P1DIR |= 0x02;                            // P1.1 = output direction

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)

  for (;;)                                  // Infinate loop
  {
    P1OUT |= 0x02;                          // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}
