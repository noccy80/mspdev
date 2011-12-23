//******************************************************************************
//  MSP430F530x Demo - Write a Word to Port B (Port3+Port4) 
//
//  Description: Writes a Word(123h) to Port B  and stays in LPM4
//  Note: Port 3 has only 5 IO's on this device
//  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//               MSP430F530x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{  
	WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT


  PBDIR |= 0x0FF0F;                         // PB.x output
  PBOUT = 0x1203;                           // Write to PortB

  __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
  __no_operation();                         // Place BREAKPOINT HERE and check register PBOUT, P3OUT and P4OUT
}
