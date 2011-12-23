//******************************************************************************
//  MSP430F552x Demo - VLO sources ACLK
//
//  Description: This program demonstrates using VLO to source ACLK
//  ACLK = VLO = 9.4kHz (typical)
//
//                 MSP430F552x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->ACLK = ~12kHz
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  UCSCTL4 |= SELA_1;                        // VLO Clock Sources ACLK

  P1DIR |= BIT0;                            // ACLK set out to pin
  P1SEL |= BIT0;

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger  
}

