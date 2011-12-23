//******************************************************************************
//  MSP430F66x Demo - VLO sources ACLK
//
//  Description: This program demonstrates using VLO to source ACLK
//  ACLK = VLO = 9.4kHz (typical)
//
//                 MSP430F66x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->ACLK = ~12kHz
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
  UCSCTL4 |= SELA_1;                        // VLO Clock Sources ACLK

  P1DIR |= BIT0;                            // ACLK set out to pin
  P1SEL |= BIT0;

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger  
}

