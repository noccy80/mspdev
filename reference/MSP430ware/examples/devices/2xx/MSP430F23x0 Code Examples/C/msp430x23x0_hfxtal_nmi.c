//******************************************************************************
//   MSP430F23x0 Demo - Basic Clock, LFXT1/MCLK Sourced from HF XTAL, NMI
//
//   Description: Proper selection of an external HF XTAL for MCLK is shown with
//   enabled OSC fault interrupt - if HF XTAL fails, NMI interrupt is requested.
//   HF XTAL can only source MCLK when OSC fault is clear. For demonstration
//   purposes P1.0 is set during OSC fault. MCLK/10 is on P1.2.
//   ACLK = MCLK = LFXT1 = HFXTAL
//   //* HF XTAL NOT INSTALLED ON FET *//
//   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//                MSP430F23x0
//             -----------------
//         /|\|              XIN|-
//          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//          --|RST          XOUT|-
//            |                 |
//            |             P1.2|-->MCLK/10
//            |             P1.0|-->LED
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   January 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x23x0.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  BCSCTL1 |= XTS;                           // LFXT1 = HF XTAL
  BCSCTL3 |= LFXT1S1;                       // 3 – 16MHz crystal or resonator
  IE1 |= OFIE;                              // Enable osc fault interrupt
  P1DIR |= 0x05;                            // P1.0,2 = output direction
  P1OUT &= ~0x01;                           // P1.0 = reset

  while (1)
  {
    P1OUT |= 0x04;                          // P1.2 = 1
    P1OUT &= ~0x04;                         // P1.2 = 0
  }
}


#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR(void)
{
  volatile unsigned int i;

  P1OUT |= 0x01;                            // P1.0 = set

  BCSCTL2 &= ~SELM_3;                       // Ensure MCLK runs from DCO
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSC fault flag
    for (i = 0xff; i; i--);                 // Delay
  } while (IFG1 & OFIFG);                   // OSC Fault, clear flag again
  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 - now safe

  P1OUT &= ~0x01;                           // P1.0 = reset
}
