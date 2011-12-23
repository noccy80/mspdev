//******************************************************************************
//  MSP430TC0701 Demo - Software Port Interrupt Service on P1.4 from LPM4
//
//  Description: A Lo/Hi transition on P1.4 will trigger P1ISR the first time. 
//  On hitting the P1ISR, device exits LPM4 mode and executes section of code in
//  main() which includes toggling an LED and the P1.4IES bit which switches between 
//  Lo/Hi and Hi/Lo trigger transitions to alternatively enter the P1ISR. 
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F552x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built IAR Embedded Workbench Version: 4.11A
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;
  P1REN |= BIT4;                            // Enable P1.4 internal resistance
  P1OUT |= BIT4;                            // Set P1.4 as pull-Up resistance
  P1IES &= ~BIT4;                           // P1.4 Lo/Hi edge
  P1IFG &= ~BIT4;                           // P1.4 IFG cleared
  P1IE |= BIT4;                             // P1.4 interrupt enabled

  while(1)
  {
    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
    __no_operation();						// For debugger
    P1OUT ^= BIT0;                          // P1.0 = toggle
    P1IES ^= BIT4;                          // Toggle between H-L and L-H transition triggers
    P1IE |= BIT4;                           // Enable port interrupt
  }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1IFG &= ~BIT4;                         // Clear P1.4 IFG
  P1IE &= ~ BIT4;                         // Clear P1.4 IE
  _BIC_SR_IRQ(LPM4_bits);                 // Exit LPM4 
}

