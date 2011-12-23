//******************************************************************************
//  MSP430F22x4 Demo - Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the ISR P1.0
//  is toggled. Toggle rate is exactly 0.5Hz. Proper use of the TBIV
//  interrupt vector generator is demonstrated.
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//           MSP430F22x4
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
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
  TBCTL = TBSSEL_1 + MC_2 + TBIE;           // ACLK, contmode, interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
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

