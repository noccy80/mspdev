//******************************************************************************
//  MSP430F51x2 Demo - Reset on Invalid Address fetch, Toggle P1.0
//
//  Description: This program demonstrates how a reset is executed if the CPU
//  tries to fetch instructions from within the module register memory address
//  range (0x0100 --0x0FEF) or from within unused address ranges. Toggle P1.0
//  by xor'ing P1.0 inside of a software loop that ends with TAR loaded with
//  3FFFh - op-code for "jmp $". This simulates a code error. The MSP430F51x2
//  will force a reset because it will not allow a fetch from within the address
//  range of the peripheral memory, as is seen by return to the mainloop and
//  LED flash.
//  ACLK = n/a, MCLK = SMCLK = default DCO 
//
//                MSP430F51x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Dec 2009
//   Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include  "msp430f5172.h"

void main(void)
{
  volatile unsigned int i;
      
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer - SET BREAKPOINT HERE
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TA0R = 0x3FFF;                            // Valid opcode (for "jmp $")

  while(1)
  {
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

    for(i = 50000; i > 0; i--);             // Delay loop 
    
    // C code to directly call an address location
    ((void (*)())0x350)();                  // Invalid fetch ("call #0350h")
    
    /* 0x350 is address of TA0R register and is within the module register memory
    address range (0x0100 --0x0FEF) */
  }                                         
}
