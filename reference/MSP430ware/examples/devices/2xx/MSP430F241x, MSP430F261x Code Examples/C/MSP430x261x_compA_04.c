//******************************************************************************
//   MSP430x26x Demo - Comparator A, Poll input CA0, result in P1.0
//
//   Description: The voltage at pin CA0 (Vcompare) is compared with reference
//   voltage of diode ref.  LED is toggled when Vcompare crosses the ref voltage.
//
//             MSP430F261x/241x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST      P2.3/CA0|<--Vcompare
//            |                 |
//            |             P1.0|-->CAOUT - LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  CACTL1 = CAON+CAREF_3+CARSEL;             //Enable comp, ref = Diode ref
  CACTL2 = P2CA0;                           // Pin to CA0

  P1DIR |= 0x001;                           // P1.0 = o/p direction (CAOUT- LED)
  P1SEL |= 0x001;                           // P1.0 - CAOUT, option select
  _BIS_SR(LPM0_bits);                       // Enter LPM0
}
