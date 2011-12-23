//******************************************************************************
//  MSP430FR57xx Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 30ms = {(1MHz) / 32768} based on DCO = SMCLK = 8MHz
//  clock source used in this example for the WDT.
//  ACLK = n/a, MCLK = SMCLK = 1MHz
//
//                MSP430FR5739
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDT_MDLY_32;                     // WDT 32ms, SMCLK, interval timer
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;        // set ACLK = VLO MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;        // set all dividers 
  
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 (LED)
}
