//******************************************************************************
//   MSP430x471xx Demo - Comparator A, Poll input CA0, result in P5.1
//
//   Description: The voltage at pin CA0 (Vcompare) is compared with reference
//   voltage of diode ref.  LED is toggled when Vcompare crosses the ref voltage.
//
//
//               MSP430x471xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST           CA0|<--Vcompare
//            |                 |
//         <--|CAOUT/P4.0       |
//            |             P5.1|-->LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  CACTL1 = CAON+CAREF_3+CARSEL;             // Enable comp, ref = Diode ref
  CACTL2 = P2CA0;                           // Pin to CA0
  CAPD |= CAPD6;                            // Port pin buffer disable
  P5DIR |= BIT1;                            // P5.1 = output direction
  P4SEL |= BIT0;                            // P4.0 = CAOUT

  while(1)
    if (CAOUT&CACTL2)
      P5OUT |= BIT1;                       // Set LED if result =1
    else
      P5OUT &= ~BIT1;                      // Set LED if result =1
}
