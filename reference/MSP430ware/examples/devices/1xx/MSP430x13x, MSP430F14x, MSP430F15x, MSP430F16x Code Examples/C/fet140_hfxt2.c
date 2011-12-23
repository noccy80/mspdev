//******************************************************************************
//  MSP-FET430P140 Demo - Basic Clock, MCLK Sourced from HF XTAL XT2
//
//  Description: Proper selection of an external HF XTAL for MCLK is shown
//  by first polling the OSC fault until XTAL is stable - only then is MCLK
//  sourced by XT2.  MCLK is on P5.4.
//  ACLK= n/a, MCLK= XT2, SMCLK= DCO,
//  //* HF XTAL NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
//
//               MSP430F149
//            -----------------
//        /|\|            XT2IN|-
//         | |                 | XTAL (455k - 8Mhz)
//         --|RST        XT2OUT|-
//           |                 |
//           |             P5.4|-->MCLK = XTAL
//
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= 0x10;                            // P5.4= output direction
  P5SEL |= 0x10;                            // P5.4= MCLK option select
  BCSCTL1 &= ~XT2OFF;                       // XT2= HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_2;                        // MCLK= XT2 (safe)

  for (;;);                                 // Do nothing
}
