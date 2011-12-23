//******************************************************************************
//  CC430F613x Demo - Reset on Invalid Address fetch, Toggle P1.0
//
//  Description: This program demonstrates how a reset is executed if the CPU
//  tries to fetch instructions from within the module register memory address
//  range (0x0100 --0x0FEF) or from within unused address ranges. Toggle P1.0
//  by xor'ing P1.0 inside of a software loop that ends with TAR loaded with
//  3FFFh - op-code for "jmp $". This simulates a code error. The CC430F6137
//  will force a reset because it will not allow a fetch from within the address
//  range of the peripheral memory, as is seen by return to the mainloop and
//  LED flash.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
//
//                CC430F6137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer - SET BREAKPOINT HERE
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TA0R = 0x3FFF;                            // Valid opcode (for "jmp $")

  while(1)
  {
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

    __delay_cycles(50000);                  // Delay loop

    // C code to directly call an address location
    ((void (*)())0x350)();                  // Invalid fetch ("call #0350h")

    /* 0x350 is address of TA0R register and is within the module register memory
    address range (0x0100 --0x0FEF) */
  }
}
