//******************************************************************************
//   MSP430F(G)47x Demo - Comparator A, Poll input CA0, interrupt triggered
//
//   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
//   voltage, an interrupt is generated, and the ISR toggles the LED.
//
//
//              MSP430F(G)47x
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

  CACTL1 = CAON+CAREF_2+CARSEL;             // Enable comp, ref = 0.5*Vcc
  CACTL2 = P2CA0;                           // Pin to CA0
  CAPD |= CAPD6;                            // Port pin buffer disable
  P4DIR |= 0x40;                            // Set P4.6 to output direction
  P2SEL |= 0x040;                           // P2.6 = CAOUT

  CACTL1 |= CAIE;                           // Setup interrupt for Comparator
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}


// Comp_A interrupt service routine -- toggles LED
#pragma vector=COMPARATORA_VECTOR
__interrupt void Comp_A_ISR (void)
{
  CACTL1 ^= CAIES;                          // Toggles interrupt edge
  P4OUT ^= 0x40;                            // Toggle P5.1
}
