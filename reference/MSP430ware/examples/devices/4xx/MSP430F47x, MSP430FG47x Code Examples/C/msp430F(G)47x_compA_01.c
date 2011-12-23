//******************************************************************************
//  MSP430F(G)47x Demo - Comparator A, Poll input CA0, result in P4.6
//
//   Description: The Voltage at pin CA0 (Vcompare) is compared with reference
//   voltage of 0.5*Vcc. LED is toggled when Vcompare crosses the ref voltage.
//
//
//                MSP430F(G)47x 
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST           CA0|<--Vcompare
//            |                 |
//            |                 |
//            |             P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  CACTL1 = CAON+CAREF_2+CARSEL;             // Enable Comp, ref = 0.5*Vcc
  CACTL2 = P2CA0;                           // Pin to CA0
  CAPD |= CAPD6;                            // Port pin buffer disable
  P4DIR |= 0x40;                            // Set P4.6 to output direction
  P2SEL |= BIT6;                            // P2.6 = CAOUT
  while(1)
  {
    if (CACTL2&0x01)
      P4OUT |= 0x40;                        // Set LED if result =1
    else
      P4OUT &= ~0x40;                       // Clear LED if result =0
  }
}
