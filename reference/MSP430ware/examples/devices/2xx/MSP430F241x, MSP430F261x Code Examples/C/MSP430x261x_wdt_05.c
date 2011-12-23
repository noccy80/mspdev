//******************************************************************************
//  MSP430x26x Demo - Reset on Invalid Address fetch, Toggle P1.0
//
//  Description: This program demonstrates how a reset is executed if the CPU 
//  tries to fetch instructions from within the module register memory address 
//  range (0x0000 --0x01FF) or from within unused address ranges. Toggle P1.0 
//  by xor'ing P1.0 inside of a software loop that ends with TAR loaded with 
//  3FFFh - op-code for "jmp $". This simulates a code error. The MSP430F229 
//  will force a reset because it will not allow a fetch from within the address 
//  range of the peripheral memory, as is seen by return to the mainloop and 
//  LED flash.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
//
//                MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  B. Nisargax
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer - SET BREAKPOINT HERE
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TAR = 0x3FFF;                             // Valid opcode (for "jmp $")

  for (;;)
  {
    volatile unsigned int i;

    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    // C code to directly call an address location
    ((void (*)())0x170)();                  // Invalid fetch ("call #0170h")
    /* 0x170 is address of TAR register and is within the module register memory 
    address range (0x0000 --0x01FF) */                                       
  }                                         // ** Should never get here **
}
