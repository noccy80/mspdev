//******************************************************************************
//  MSP430F543xA Demo - VLO sources ACLK. Toggles P1.0
//
//  Description: This program demonstrates using VLO to source ACLK
//  ACLK = VLO = ~12kHz	
//
//                 MSP430F5438A
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |            P11.0|--> ACLK = ~10kHz
//            |                 |
//            |             P1.0|-->LED
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDT_ADLY_250;                    // WDT ~1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt

  P1DIR |= BIT0;                            // P1.0 to output direction
  P11DIR |= BIT0;                           // P11.0 to output direction
  P11SEL |= BIT0;                           // P11.0 to output ACLK

  UCSCTL4 |= SELA_1;                        // VLO Clock Sources ACLK

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // For debugger
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}
