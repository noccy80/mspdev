//******************************************************************************
//  MSP430FR57xx Demo - Software Port Interrupt Service on P1.4 from LPM4
//
//  Description: A Lo/Hi transition on P1.4 will trigger P1ISR the first time. 
//  On hitting the P1ISR, device exits LPM4 mode and executes section of code in
//  main() which includes toggling an LED and the P1.4IES bit which switches between 
//  Lo/Hi and Hi/Lo trigger transitions to alternatively enter the P1ISR. 
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430FR5739
//            -----------------
//        /|\|                 |-
//         | |                 |
//         --|RST              |-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;
  P1OUT &= ~BIT4;                           // 
  P1IES &= ~BIT4;                           // P1.4 Lo/Hi edge
  P1IE = BIT4;                              // P1.4 interrupt enabled
  P1IFG &= ~BIT4;                           // P1.4 IFG cleared
  

  while(1)
  {
    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
    __no_operation();			    // For debugger
    P1OUT ^= BIT0;                          // P1.0 = toggle
    P1IE = BIT4;                            // P1.4 interrupt enabled   

  }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1IES ^= BIT4;    
  P1IFG &= ~BIT4;                         // Clear P1.4 IFG
  P1IE = 0;
  __bic_SR_register_on_exit(LPM4_bits);     // Exit LPM4 
}

