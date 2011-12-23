//******************************************************************************
//   MSP430x24x Demo - Comparator A, Poll input CA0, interrupt triggered
//
//   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
//   voltage, an interrupt is generated, and the ISR toggles the LED.
//
//                 MSP430F249
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST      P2.3/CA0|<--Vcompare
//            |                 |
//            |             P1.0|-->I/O - LED
//
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x24x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  CACTL1 = CAON+CAREF_2+CARSEL;             // Enable comp, ref = 0.5*Vcc
  CACTL2 = P2CA0;                           // Pin to CA0

  P1DIR |= 0x001;                           // P1.0 = o/p direction 

  CACTL1 |= CAIE;                           // Setup interrupt for Comparator
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}

// Comp_A interrupt service routine -- toggles LED
#pragma vector=COMPARATORA_VECTOR
__interrupt void Comp_A_ISR (void)
{
  CACTL1 ^= CAIES;                          // Toggles interrupt edge
  CACTL1 &= ~CAIFG;                         // Clear Interrupt flag
  P1OUT ^= 0x01;                            // Toggle P1.0
}
