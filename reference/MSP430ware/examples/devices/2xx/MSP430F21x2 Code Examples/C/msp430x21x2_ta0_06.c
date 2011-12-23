//******************************************************************************
//  MSP430F21x1 Demo - Timer0_A3, Toggle P1.0, TA0CCR1 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer0_A1 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TA0CLK.
//  During the Timer0_A1 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  TA0CCR0. Timer0_A1 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during Timer0_A1 ISR. Proper use of the TA0IV interrupt vector generator
//  is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TA0CLK = default DCO ~1.2MHz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA0CCTL1 = CCIE;                          // TACCR1 interrupt enabled
  TA0CCR1 = 50000;
  TA0CTL = TASSEL_2 + MC_2;                 // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer0_A1 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
  switch (__even_in_range(TAIV, 10))        // Efficient switch-implementation
  {
    case  2:                                // TACCR1
      P1OUT ^= 0x01;                        // Toggle P1.0
      TACCR1 += 50000;                      // Add Offset to TACCR1
      break;
    case  4: break;                         // TACCR2 not used
    case 10: break;                         // Overflow not used
  }
}
