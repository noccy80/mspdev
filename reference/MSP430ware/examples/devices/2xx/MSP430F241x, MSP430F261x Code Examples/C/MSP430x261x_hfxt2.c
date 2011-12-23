//******************************************************************************
//  MSP430x26x Demo - Basic Clock, MCLK Configured to Operate from XT2 HF XTAL
//
//  Description: Proper selection of an external HF XTAL for MCLK is shown
//  using HF XT2 OSC. OFIFG is polled until the HF XTAL is stable; only then is 
//  MCLK sourced by XT2.  MCLK is buffered on P5.4 and MCLK/10 is on P1.1 driven 
//  by a software loop taking exactly 10 CPU cycles.
//  ACLK = MCLK = LFXT1 = HF XTAL, SMCLK = default DCO ~1.045MHz
//  //* XT2 HF XTAL NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//              MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |                 |
//            |            XT2IN|-
//            |                 | HF XTAL (400kHz - 16MHz)
//            |           XT2OUT|-
//            |                 |
//            |             P1.1|-->MCLK/10 = XT2 HFXTAL/10
//            |        P5.4/MCLK|-->MCLK = XT2 HFXTAL
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P5DIR |= 0x10;                            // P5.4= output direction
  P5SEL |= 0x10;                            // P5.4= MCLK option select
  P1DIR |= 0x02;                            // P1.1 = output direction

  BCSCTL1 &= ~XT2OFF;                       // Activate XT2 high freq xtal
  BCSCTL3 |= XT2S_2;                        // 3 – 16MHz crystal or resonator

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?

  BCSCTL2 |= SELM_2;                        // MCLK = XT2 HF XTAL (safe)

  for (;;)                                  // Infinite loop
  {
    P1OUT |= 0x02;                          // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}
