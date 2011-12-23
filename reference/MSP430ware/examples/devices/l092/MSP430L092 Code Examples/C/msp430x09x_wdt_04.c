/*********************************************************************************/
/*  MSP430L092 Demo - Reset on Invalid Address fetch, Toggle P1.0                */
/*                                                                               */
/*  Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop that      */
/*  ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code  */
/*  error. The MSP430L029 will force a reset because it will not allow a fetch   */
/*  from within the address range of the peripheral memory, as is seen by        */
/*  return to the mainloop and P1.0 toggle.                                      */
/*                                                                               */
/*                                                                               */
/*                MSP430L092                                                     */
/*             -----------------                                                 */   
/*         /|\|              XIN|-                                               */
/*          | |                 |                                                */
/*          --|RST          XOUT|-                                               */
/*            |                 |                                                */
/*            |             P1.0|-->Out                                          */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/
#include "msp430l092.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  TA0R |= 0x3FFF;                            // Opcode for "jmp $"

 while(1)
  {
    volatile unsigned int i;

    P1OUT ^= BIT0;                          // Toggle P1.0 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    ((void (*)())0x350)();                  // Invalid fetch ("call #0170h")
  }                                         // ** Should never get here **
}
