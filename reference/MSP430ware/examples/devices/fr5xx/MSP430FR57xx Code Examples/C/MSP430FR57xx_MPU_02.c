//******************************************************************************
//  MSP430FR57x Demo - MPU Write protection violation - PUC
//
//  Description: The MPU segment boundaries are defined by:
//  Border 1 = 0xC800 [segment #: 4]
//  Border 2 = 0xD000 [segment #: 8]
//  Segment 1 = 0xC200 - 0xC7FF
//  Segment 2 = 0xC800 - 0xCFFF
//  Segment 3 = 0xD000 - 0xFFFF
//  Segment 2 is write protected. Any write to an address in the segment 2 range
//  causes a PUC. The LED toggles due to repeated PUCs. A delay is included
//  so the debugger can gain access via JTAG.
//
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO = ~625 KHz
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"

unsigned int *ptr = 0;
unsigned int Data =0;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT 
  
  P1DIR |= BIT0;                            // Configure P1.0 for LED
  if (MPUCTL1 & MPUSEG2IFG)                 // has reset occured due to Seg2
  { 
  P1OUT ^= BIT0;                            // Toggle LED
  }
  __delay_cycles(30000);                    // Delay to see toggle

  // Configure MPU 
  MPUCTL0 = MPUPW;                          // Write PWD to access MPU registers
  MPUSEG = 0x0804;                          // B1 = 0xC800; B2 = 0xD000
                                            // Borders are assigned to segments
  MPUSAM &= ~MPUSEG2WE;                     // Segment 2 is protected from write
  MPUSAM |= MPUSEG2VS;                      // Violation select on write access
  
  MPUCTL0 = MPUPW+MPUENA+MPULOCK;           // Enable MPU protection
                                            // MPU registers locked until BOR
  Data = 0x88;
  
  // Cause an MPU violation by writing to segment 2
  ptr = (unsigned int  *)0xC802; 
  *ptr = Data;   
  
 
  while(1);                                 // Code never gets here

}


  
