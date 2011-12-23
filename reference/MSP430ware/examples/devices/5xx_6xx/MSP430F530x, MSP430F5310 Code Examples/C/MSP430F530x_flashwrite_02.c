//******************************************************************************
//  MSP430F530x Demo - Flash In-System Programming w/ Long-Word write at 0x1800
//
//  Description: This program first erases flash seg D, then it writes a 32-bit
//  value to memory location 0x1800 using long-word write mode. Long-word write
//  provides faster write than byte/word mode.
//  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//
//                MSP430F530x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  unsigned long * Flash_ptrD;               // Initialize Flash pointer Seg D
  unsigned long value;
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  Flash_ptrD = (unsigned long *) 0x1800;    // Initialize Flash pointer
  value = 0x12345678;                       // Initialize Value
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *Flash_ptrD = 0;                          // Dummy write to erase Flash seg
  FCTL1 = FWKEY+BLKWRT;                     // Enable long-word write
  *Flash_ptrD = value;                      // Write to Flash
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
  while(1);                                 // Loop forever, SET BREAKPOINT HERE
}
