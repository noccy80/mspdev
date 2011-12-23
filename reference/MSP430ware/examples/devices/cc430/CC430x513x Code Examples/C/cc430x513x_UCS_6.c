//******************************************************************************
//  CC430F513x Demo - XT1 sources ACLK. Toggles P1.0
//
//  Description: This program demonstrates using XT1 to source ACLK
//  ACLK = LFXT1 = 32,768Hz	
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//               CC430F5137
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |            P2.0 |--> ACLK = ~32kHz
//            |                 |
//            |             P1.0|-->LED
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDT_ADLY_1000;                   // WDT 1000ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt

  P1DIR |= BIT0;                            // P1.0 to output direction

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP0 = PM_ACLK;                         // Map ACLK output to P2.0 
  PMAPPWD = 0;                              // Lock port mapping registers  
   
  P2DIR |= BIT0;                            // ACLK, MCLK, SMCLK set out to pins
  P2SEL |= BIT0;                            // P2.0 for debugging purposes

  P5SEL |= 0x03;                            // Select XT1
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive
                                            // strength

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
  __no_operation();                         // For debugger
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}
