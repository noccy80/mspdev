//******************************************************************************
//   MSP430xG46x Demo - Comparator A, Poll input CA0, result in P5.1
//
//   Description: The Voltage at pin CA0 (Vcompare) is compared with reference
//   voltage of 0.5*Vcc. LED is toggled when Vcompare crosses the ref voltage.
//
//
//                 MSP430xG461x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST           CA0|<--Vcompare
//            |                 |
//            |                 |
//            |             P5.1|-->LED
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  CACTL1 = CAON+CAREF_2+CARSEL;             // Enable Comp, ref = 0.5*Vcc
  CACTL2 = P2CA0;                           // Pin to CA0

  P5DIR |= 0x002;                           // P5.1 = output direction
  P2SEL |= 0x040;                           // P2.6 = CAOUT

  while(1)
    if (CACTL2&0x01)
      P5OUT |= 0x002;                       // Set LED if result =1
    else
      P5OUT &= ~0x002;                      // Set LED if result =1
}
