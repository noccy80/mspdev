//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer0_A1 overflow ISR.
//  In this example an ISR triggers when TA0 overflows. Inside the TA
//  overflow ISR P1.0 is toggled. Toggle rate is approximately 18Hz.
//  Proper use of the TA0IV interrupt vector generator is demonstrated.
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
//  December 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA0CTL = TASSEL_2 + MC_2 + TAIE;          // SMCLK, contmode, interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer0_A1 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void)
{
  switch  (__even_in_range(TA0IV, 10))       // Efficient switch-implementation
  {
    case  2: break;                         // TA0CCR1 not used
    case  4: break;                         // TA0CCR2 not used
    case 10: P1OUT ^= 0x01;                 // overflow
             break;
  }
}

