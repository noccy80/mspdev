//******************************************************************************
//   MSP430F22x4 Demo - Timer_B, Toggle P1.0, TBCCR1 Cont. Mode ISR, DCO SMCLK
//
//   Description: Toggle P1.0 using software and TB_1 ISR. Toggles every
//   50000 SMCLK cycles. SMCLK provides clock source for TBCLK.
//   During the TB_1 ISR, P1.0 is toggled and 50000 clock cycles are added to
//   TBCCR1. TB_1 ISR is triggered every 50000 cycles. CPU is normally off and
//   used only during TB_ISR. Proper use of the TBIV interrupt vector generator
//   is demonstrated.
//   ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.2MHz
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   April 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TBCCTL1 = CCIE;                           // TBCCR1 interrupt enabled
  TBCCR1 = 50000;
  TBCTL = TBSSEL_2 + MC_2;                  // SMCLK, contmode

  __bis_SR_register(CPUOFF + GIE);          // CPU off, interrupts enabled
}

// Timer_B3 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
  switch (TBIV)        // Efficient switch-implementation
  {
    case  2:                                // TBCCR1
      TBCCR1 += 50000;                      // Offset until next interrupt
      P1OUT ^= 0x01;                        // Toggle P1.0
      break;
    case  4: break;                         // TBCCR2 not used
    case 14: break;                         // Overflow not used
  }
}
