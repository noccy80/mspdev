//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_1 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_1 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  TACCR0. TA_1 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR. Proper use of the TAIV interrupt vector generator
//  is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TACCTL1 = CCIE;                           // TACCR1 interrupt enabled
  TACCR1 = 50000;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch (TAIV, 10)        // Efficient switch-implementation
  {
    case  2:                                // TACCR1
      P1OUT ^= 0x01;                        // Toggle P1.0
      TACCR1 += 50000;                      // Add Offset to TACCR1
      break;
    case  4: break;                         // TACCR2 not used
    case 10: break;                         // Overflow not used
  }
}
