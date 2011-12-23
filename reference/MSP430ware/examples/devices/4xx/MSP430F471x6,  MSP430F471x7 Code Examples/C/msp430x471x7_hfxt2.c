//******************************************************************************
//   MSP430x471xx Demo - FLL+, MCLK Configured to Operate from XT2 HF XTAL
//
//   Description: Proper selection of an external HF XTAL for MCLK is
//   demonstrated using HF XT2 OSC.  OFIFG is polled until the HF XTAL
//   is stable - only then is MCLK sourced by XT2.  MCLK is buffered on P1.1.
//   //** HF XTAL NOT INSTALLED ON FET **//
//
//                MSP430x471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |                 |
//            |            XT2IN|-
//            |                 | HF XTAL (455kHz - 16MHz)
//            |           XT2OUT|-
//            |                 |
//            |                 |
//            |        P1.1/MCLK|-->MCLK = HF XTAL
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include  <msp430x471x7.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  _BIS_SR(OSCOFF + SCG0 + GIE);             // Disable LFXT1 xtal osc & FLL loop

  FLL_CTL1 &= ~XT2OFF;                      // Activate XT2 high freq xtal

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 5; i > 0; i--);                  // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  FLL_CTL1 |= SELM1;                        // MCLK = XT2

  P1DIR |= BIT1;                            // P1.1 output direction
  P1SEL |= BIT1;                            // P1.1 option select

  while(1);
}
