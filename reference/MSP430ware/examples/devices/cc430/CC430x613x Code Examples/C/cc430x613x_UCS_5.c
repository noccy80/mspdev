//******************************************************************************
//  CC430F613x Demo - VLO sources ACLK. Toggles P1.0
//
//  Description: This program demonstrates using VLO to source ACLK
//  ACLK = VLO = ~10kHz	
//
//                 CC430F6137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |            P2.0 |--> ACLK = ~10kHz
//            |                 |
//            |             P1.0|-->LED
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDT_ADLY_250;                    // WDT ~1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt

  P1DIR |= BIT0;                            // P1.0 to output direction

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_ACLK;                         // Map ACLK output to P2.0 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0;                            // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0;                            // P2.0 for debugging purposes

  UCSCTL4 |= SELA__VLOCLK;                  // VLO Clock Sources ACLK

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // For debugger
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}
