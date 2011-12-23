//******************************************************************************
//   MSP430x41x2 Demo - Comparator A, Poll input CA0, CA exchange, result P5.1
//
//   Description: The Voltage at pin CA0 (Vcompare) is compared with reference
//   voltage of 0.5*Vcc. LED is toggled when Vcompare crosses the ref voltage.
//
//
//              MSP430x41x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST           CA0|<--Vcompare
//            |                 |
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  CACTL1 = CAEX+CAON+CAREF_2+CARSEL;        // Enable comp,
  CACTL2 = P2CA0;                           // Pin to CA0
  CAPD |= CAPD6;                            // Port pin buffer disable
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  P1DIR |= 0x20;                            // P1.5 = CAOUT
  P1SEL |= 0x20;                            // P1.5 = CAOUT

  while(1)
  {
    if (CACTL2&0x01)
      P5OUT |= 0x02;                        // Set LED if result =1
    else
      P5OUT &= ~0x02;                       // Clear LED if result =0

  }
}
