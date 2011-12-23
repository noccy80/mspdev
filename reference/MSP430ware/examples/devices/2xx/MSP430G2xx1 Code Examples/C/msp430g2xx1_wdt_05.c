//******************************************************************************
//   MSP430G2xx1 Demo - Reset on Invalid Address fetch, Toggle P1.0
//
//  Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop that
//  ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code
//  error. The MSP430F21x1 will force a reset because it will not allow a fetch
//  from within the address range of the peripheral memory, as is seen by
//  return to the mainloop and LED flash.
//  In contrast, an MSP430F1xx device will "jmp $" stopping code execution with
//  no LED flash.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430G2xx1
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  H. Grewal / M. Buccini
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TAR = 0x3FFF;                             // Opcode for "jmp $"

  for (;;)
  {
    volatile unsigned int i;

    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    ((void (*)())0x170)();                  // Invalid fetch ("call #0170h")
  }
}
