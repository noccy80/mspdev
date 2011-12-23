//******************************************************************************
//  MSP430F66x Demo - XT1 sources ACLK
//
//  Description: This program demonstrates using XT1 to source ACLK
//  ACLK = LFXT1 = 32,768Hz	
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//               MSP430F66x
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |             P1.0|-->ACLK = ~32kHz
//            |                 |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= BIT0;                            // ACLK set out to pin
  P1SEL |= BIT0;
  P5SEL |= BIT4+BIT5;                       // Select XT1

  while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
     BAKCTL &= ~(LOCKIO); 
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap 
  // Loop until XT1 fault flag is cleared
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength

  UCSCTL4 |= SELA_0;                        // ACLK = LFTX1 (by default)
  
  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

