//******************************************************************************
//  MSP430F22x4 Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the TB
//  overflow ISR P1.0 is toggled. Toggle rate is approximatlely 18Hz.
//  Proper use of the TBIV interrupt vector generator is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.2MHz
//
//           MSP430F22x4
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
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
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCTL = TBSSEL_2 + MC_2 + TBIE;           // SMCLK, contmode, interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_B3 Interrupt Vector (TBIV) handler
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B(void)
{
  switch (TBIV)        // Efficient switch-implementation
  {
    case  2: break;                         // TBCCR1 not used
    case  4: break;                         // TBCCR2 not used
    case 14: P1OUT ^= 0x01;                 // overflow
             break;
  }
}

