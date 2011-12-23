//******************************************************************************
//  MSP430x471xx Demo - Reset on Invalid Address fetch, Toggle P5.1
//
//  Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop that
//  ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code
//  error. The MSP430x47x4 will force a reset because it will not allow a fetch
//  from within the address range of the peripheral memory, as is seen by
//  return to the mainloop and LED flash.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//                MSP430x471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "msp430x471x7.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= BIT1;                            // Set P5.1 to output direction
  TAR = 0x3FFF;                             // Opcode for "jmp $"

  for (;;)
  {
    volatile unsigned int i;

    P5OUT ^= BIT1;                          // Toggle P5.1 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    ((void (*)())0x170)();                  // Invalid fetch ("call #0170h")
    _NOP();                                // ** Should never get here **
  }         
}
